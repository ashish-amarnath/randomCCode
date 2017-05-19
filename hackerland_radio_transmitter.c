#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

const char EMPTY = 'E';
const char OCCUPIED = 'O';
const char COVERED = 'C';

char *lane = NULL;
int lane_size = 0;
int transmitters_added = 0;

int get_max_house_no(int *a, int n) {
    int max = -1;
    int i = 0;
    for (i = 0; i < n; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}

void init_lane() {
    int i = 0;
    lane = (char*) malloc(sizeof(char) * lane_size);
    for (i = 0; i < lane_size; i++) {
        lane[i] = EMPTY;
    }    
}

void set_occupied_lots(int *x, int n) {
    int i = 0;
    for(i = 0; i < n; i++) {
        assert(x[i] < lane_size);
        lane[x[i]] = OCCUPIED;
    }
}

void print_lane() {
    int i = 0;
    for(i = 1; i < lane_size; i++) {
        printf("[%d:%c] ", i, lane[i]);
    }
    printf("\n");
}

int are_all_houses_covered() {
    int all_covered = 1;
    int i = 0;
    for (i = 1; i < lane_size; i++) {
        if (lane[i] == OCCUPIED) {
            all_covered = 0;
            break;
        }
    }
    return all_covered;
}

void mark_coverage(int i) {    
    if (lane[i] == OCCUPIED) {
        lane[i] = COVERED;
    }
}

int add_transmitter(int loc, int range) {
    int i = 0;
    int left_bound = -1;
    int right_bound = -1;
    int last_covered = -1;
    lane[loc] = COVERED;
    right_bound = (loc + range) > (lane_size - 1) ? (lane_size - 1) : (loc + range);
    for (i = loc; i <= right_bound; i++) {
        mark_coverage(i);
        if (lane[i] == COVERED) {
            last_covered = i;
        }
    }
    left_bound = (loc - range) < 0 ? 0 : (loc - range);
    for(i = loc; i >= left_bound; i--) {
        mark_coverage(i);
    }
    transmitters_added++;
    return last_covered;
}

void reset_coverage() {
    int i = 0;
    for (i = 0; i < lane_size; i++) {
        if (lane[i] == COVERED) {
            lane[i] = OCCUPIED;
        }
    }
}

int get_next_occupied() {
    int i = 0;
    for(i = 1; i < lane_size; i++) {
        if (lane[i] == OCCUPIED) {
            break;
        }
    }
    return i;
}

int find_last_occupied_in_range(int start, int end) {
    int i = 0;
    for (i = end; i >= start; i--) {
        if (lane[i] == OCCUPIED) {
            break;
        }
    }
    return i;
}

int main() {
    int n; 
    int k; 
    int max_house_no = -1;
    scanf("%d %d",&n,&k);
    int *x = malloc(sizeof(int) * n);
    for(int x_i = 0; x_i < n; x_i++){
       scanf("%d",&x[x_i]);
    }
    lane_size = get_max_house_no(x, n);
    lane_size++;
    init_lane();
    set_occupied_lots(x, n);
    
    int next_occupied = -1;
    int start_loc = -1;
    int last_touched = 0;
    while(true) {
        next_occupied = get_next_occupied(last_touched + 1);
        if (next_occupied == lane_size) {
            //print_lane();
            assert(are_all_houses_covered());
            break;
        }
        start_loc = find_last_occupied_in_range(next_occupied, next_occupied + k);

        last_touched = add_transmitter(start_loc, k);
    }
    
    //print_lane();
    
    printf("%d\n", transmitters_added);
    
    return 0;
}

