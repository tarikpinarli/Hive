#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_EVENTS 1000
#define MAX_LINE_LENGTH 512
#define DAILY_START 9 * 60       // 09:00 in minutes
#define DAILY_END 22 * 60        // 22:00 in minutes
#define DAILY_MINUTES (DAILY_END - DAILY_START)

typedef struct {
    char summary[256];
    struct tm start_tm;
    struct tm end_tm;
    time_t start_utc;
} Event;

typedef struct {
    int busy_minutes[DAILY_MINUTES];
} DayBusyMap;

int parse_dt_to_tm(const char *dt_str, struct tm *tm_out) {
    if (strlen(dt_str) < 16) return 0;
    char buf[5];
    memset(tm_out, 0, sizeof(struct tm));

    strncpy(buf, dt_str, 4); buf[4] = '\0';
    tm_out->tm_year = atoi(buf) - 1900;

    strncpy(buf, dt_str + 4, 2); buf[2] = '\0';
    tm_out->tm_mon = atoi(buf) - 1;

    strncpy(buf, dt_str + 6, 2); buf[2] = '\0';
    tm_out->tm_mday = atoi(buf);

    strncpy(buf, dt_str + 9, 2); buf[2] = '\0';
    tm_out->tm_hour = atoi(buf);

    strncpy(buf, dt_str + 11, 2); buf[2] = '\0';
    tm_out->tm_min = atoi(buf);

    strncpy(buf, dt_str + 13, 2); buf[2] = '\0';
    tm_out->tm_sec = atoi(buf);

    tm_out->tm_isdst = -1;
    return 1;
}

void add_timezone_offset(struct tm *time, int offset_hours) {
    time_t raw = timegm(time);
    raw += offset_hours * 3600;
    *time = *gmtime(&raw);
}

int process_calendar(const char *filename, time_t now, time_t one_month_later, Event *events, int event_count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "❌ Error opening file: %s\n", filename);
        return event_count;
    }

    char line[MAX_LINE_LENGTH];
    int inside_event = 0;

    char summary[256] = "";
    char dtstart[32] = "";
    char dtend[32] = "";

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\r\n")] = 0;

        if (strcmp(line, "BEGIN:VEVENT") == 0) {
            inside_event = 1;
            summary[0] = '\0';
            dtstart[0] = '\0';
            dtend[0] = '\0';
        } else if (strcmp(line, "END:VEVENT") == 0) {
            inside_event = 0;

            struct tm start_tm, end_tm;
            if (parse_dt_to_tm(dtstart, &start_tm) && parse_dt_to_tm(dtend, &end_tm)) {
                time_t start_utc = timegm(&start_tm);
                if (start_utc >= now && start_utc <= one_month_later && event_count < MAX_EVENTS) {
                    add_timezone_offset(&start_tm, 3);
                    add_timezone_offset(&end_tm, 3);

                    Event e;
                    strncpy(e.summary, summary, sizeof(e.summary));
                    e.start_tm = start_tm;
                    e.end_tm = end_tm;
                    e.start_utc = start_utc;
                    events[event_count++] = e;
                }
            }
        }

        if (inside_event) {
            if (strncmp(line, "DTSTART:", 8) == 0) {
                strncpy(dtstart, line + 8, sizeof(dtstart));
            } else if (strncmp(line, "DTEND:", 6) == 0) {
                strncpy(dtend, line + 6, sizeof(dtend));
            } else if (strncmp(line, "SUMMARY:", 8) == 0) {
                strncpy(summary, line + 8, sizeof(summary));
            }
        }
    }

    fclose(file);
    return event_count;
}

void mark_busy_for_day(DayBusyMap *map, struct tm start, struct tm end) {
    if (start.tm_year != end.tm_year || start.tm_mon != end.tm_mon || start.tm_mday != end.tm_mday) return;

    int start_min = start.tm_hour * 60 + start.tm_min;
    int end_min = end.tm_hour * 60 + end.tm_min;

    // Clamp to activity range
    if (end_min <= DAILY_START || start_min >= DAILY_END) return;

    int from = (start_min < DAILY_START) ? 0 : start_min - DAILY_START;
    int to = (end_min > DAILY_END) ? DAILY_MINUTES : end_min - DAILY_START;

    for (int i = from; i < to; i++) {
        map->busy_minutes[i] = 1;
    }
}

void print_common_free_time(const char *date_str, DayBusyMap *m1, DayBusyMap *m2) {
    int i = 0;
    int in_free = 0;
    int free_start = 0;

    for (i = 0; i <= DAILY_MINUTES; i++) {
        int is_end = (i == DAILY_MINUTES);
        int both_free = (!is_end && m1->busy_minutes[i] == 0 && m2->busy_minutes[i] == 0);

        if (!in_free && both_free) {
            in_free = 1;
            free_start = i;
        } else if (in_free && (!both_free || is_end)) {
            in_free = 0;
            int duration = i - free_start;

            if (duration >= 120) {  // ✅ Only print if free time is 2 hours or longer
                int s_hr = (free_start + DAILY_START) / 60;
                int s_min = (free_start + DAILY_START) % 60;
                int e_hr = (i + DAILY_START) / 60;
                int e_min = (i + DAILY_START) % 60;

                printf("%s | Both Free: from %02d:%02d to %02d:%02d\n", date_str, s_hr, s_min, e_hr, e_min);
            }
        }
    }
}


void analyze_common_free_slots(Event *events1, int count1, Event *events2, int count2) {
    for (int d = 0; d < 30; d++) {
        time_t base = time(NULL) + d * 24 * 60 * 60;
        struct tm day_tm = *gmtime(&base);
        add_timezone_offset(&day_tm, 3);

        char date_str[11];
        snprintf(date_str, sizeof(date_str), "%04d-%02d-%02d", day_tm.tm_year + 1900, day_tm.tm_mon + 1, day_tm.tm_mday);

        DayBusyMap u1 = {0}, u2 = {0};
        int found1 = 0, found2 = 0;

        for (int i = 0; i < count1; i++) {
            if (events1[i].start_tm.tm_year == day_tm.tm_year &&
                events1[i].start_tm.tm_mon == day_tm.tm_mon &&
                events1[i].start_tm.tm_mday == day_tm.tm_mday) {
                mark_busy_for_day(&u1, events1[i].start_tm, events1[i].end_tm);
                found1 = 1;
            }
        }

        for (int i = 0; i < count2; i++) {
            if (events2[i].start_tm.tm_year == day_tm.tm_year &&
                events2[i].start_tm.tm_mon == day_tm.tm_mon &&
                events2[i].start_tm.tm_mday == day_tm.tm_mday) {
                mark_busy_for_day(&u2, events2[i].start_tm, events2[i].end_tm);
                found2 = 1;
            }
        }

        if (found1 || found2) {
            print_common_free_time(date_str, &u1, &u2);
        }
    }
}

int main() {
    time_t now = time(NULL);
    time_t one_month_later = now + (30 * 24 * 60 * 60);

    Event events1[MAX_EVENTS];
    Event events2[MAX_EVENTS];
    int count1 = 0, count2 = 0;

    count1 = process_calendar("calendar.ics", now, one_month_later, events1, count1);
    count2 = process_calendar("calendar2.ics", now, one_month_later, events2, count2);

    printf("🔍 Detecting common free time from 09:00 to 22:00 each day...\n\n");
    analyze_common_free_slots(events1, count1, events2, count2);

    return 0;
}
