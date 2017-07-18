#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>

#define BACKLIGHTPATH "/sys/class/backlight/intel_backlight/"
#define BRIGHTNESSFILEPATH BACKLIGHTPATH "brightness"
#define MAXBRIGHTNESSFILEPATH BACKLIGHTPATH "max_brightness"

void usage(char *program) {
    printf("Usage: %s {-get|-set NUM|-inc NUM|-dec NUM}\n", program);
}

int read_int_from_file(const char* path) {
    FILE *fp;
    int value;
    fp = fopen(path, "r");
    fscanf(fp, "%d", &value);
    fclose(fp);
    return value;
}

void write_int_to_file(const char* path, int value) {
    FILE *fp;
    fp = fopen(path, "w");
    fprintf(fp, "%d", value);
    fclose(fp);
}

int max_brightness() {
    return read_int_from_file(MAXBRIGHTNESSFILEPATH);
}

int cur_brightness() {
    return read_int_from_file(BRIGHTNESSFILEPATH);
}

void get() {
    printf("%d\n", cur_brightness());
}

void set(int amount) {
    write_int_to_file(BRIGHTNESSFILEPATH, amount);
}

bool folder_exists() {
    struct stat sb;
    if (stat(BACKLIGHTPATH, &sb) == 0 && S_ISDIR(sb.st_mode)) {
        return true;
    } else {
        return false;
    }
}

int main(int argc, char** argv ) {

    if (argc < 2) {
        usage(argv[0]);
        exit(1);
    }

    if (! folder_exists()) {
        printf("Error: %s does not exist!\n", BACKLIGHTPATH);
        exit(1);
    }

    if (strcmp("-get", argv[1]) == 0) {
        get();
        exit(0);
    } else if(strcmp("-set", argv[1]) == 0) {
        if (argc < 3) {
            usage(argv[0]);
            exit(1);
        }
        int amount = atoi(argv[2]);
        if (amount < 0) {
            printf("Value %d is negative!\n", amount);
            exit(1);
        }
        int maxbg = max_brightness();
        if (amount > maxbg) {
            printf("Value %d is bigger than the maximum %d!\n", amount, maxbg);
            exit(1);
        }
        set(amount);
        exit(0);
    } else if(strcmp("-inc", argv[1]) == 0) {
        if (argc < 3) {
            usage(argv[0]);
            exit(1);
        }
        int amount = atoi(argv[2]);
        if (amount < 0) {
            printf("Value %d is negative!\n", amount);
            exit(1);
        }
        int maxbg = max_brightness();
        int curbg = cur_brightness();

        if (curbg + amount > maxbg) {
            set(maxbg);
            exit(0);
        }
        set(curbg + amount);
        exit(0);
    } else if(strcmp("-dec", argv[1]) == 0) {
        if (argc < 3) {
            usage(argv[0]);
            exit(1);
        }
        int amount = atoi(argv[2]);
        if (amount < 0) {
            printf("Value %d is negative!\n", amount);
            exit(1);
        }
        int maxbg = max_brightness();
        int curbg = cur_brightness();

        if (curbg - amount < 0) {
            set(0);
            exit(0);
        }
        set(curbg - amount);
        exit(0);
    }

    exit(0);

}

