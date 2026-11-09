#include <stdio.h> 
#include <stdlib.h>
 #include <unistd.h> 
 #include <sys/statvfs.h> 
 #include <gpiod.h>

#define LED_PIN 17

float getMemory() { FILE *file = fopen("/proc/meminfo", "r"); long total = 0, available = 0; char line[100];

if (file == NULL)
    return -1;

while (fgets(line, sizeof(line), file)) {
    sscanf(line, "MemTotal: %ld kB", &total);
    sscanf(line, "MemAvailable: %ld kB", &available);
}

fclose(file);

if (total == 0)
    return -1;

return 100.0 * (total - available) / total;
}

float getStorage() { struct statvfs disk;

if (statvfs("/", &disk) != 0)
    return -1;

if (disk.f_blocks == 0)
    return -1;

return 100.0 * (disk.f_blocks - disk.f_bfree)
       / disk.f_blocks;
}

int main(int argc, char *argv[]) { float threshold = 80.0;

if (argc > 1)
    threshold = atof(argv[1]);

if (threshold < 0 || threshold > 100) {
    printf("Invalid threshold\n");
    return 1;
}

struct gpiod_chip *chip =
    gpiod_chip_open_by_name("gpiochip0");

if (chip == NULL) {
    perror("GPIO chip");
    return 1;
}

struct gpiod_line *led =
    gpiod_chip_get_line(chip, LED_PIN);

if (led == NULL ||
    gpiod_line_request_output(led, "monitor", 0) < 0) {
    perror("GPIO LED");
    gpiod_chip_close(chip);
    return 1;
}

while (1) {
   float memory, storage;

printf("Enter memory percentage: ");
scanf("%f", &memory);

printf("Enter storage percentage: ");
scanf("%f", &storage);


    if (memory < 0 || storage < 0) {
        printf("Unable to read resources\n");
        break;
    }

    int warning = memory > threshold ||
                  storage > threshold;

    printf("\nMemory: %.1f%%\n", memory);
    printf("Storage: %.1f%%\n", storage);
    printf("Threshold: %.1f%%\n", threshold);

    if (warning)
        printf("Status: WARNING\n");
    else
        printf("Status: HEALTHY\n");

    gpiod_line_set_value(led, warning);

    FILE *file = fopen("results.txt", "a");

    if (file != NULL) {
        fprintf(file,
            "Memory: %.1f%% Storage: %.1f%% Status: %s\n",
            memory, storage,
            warning ? "WARNING" : "HEALTHY");
        fclose(file);
    }

    sleep(5);
}

gpiod_line_set_value(led, 0);
gpiod_line_release(led);
gpiod_chip_close(chip);

return 0;
}