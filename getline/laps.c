#include "laps.h"

typedef struct {
    int id;
    int laps;
} Car;

static Car *cars = NULL;
static size_t car_count = 0;

int find_car(int id) {
    for (size_t i = 0; i < car_count; i++)
    {
		if (cars[i].id == id)
		{
			return i;
		}
    }
	return -1;
}

void add_car(int id) 
{
	car_count++;
	cars = realloc(cars, car_count * sizeof(Car));
	if (cars == NULL)
	{
		exit(EXIT_FAILURE);
	}
	cars[car_count - 1].id = id;
	cars[car_count - 1].laps = 0;
	printf("Car %d joined the race\n", id);
}

void bubble_sort_cars() {
    for (size_t i = 0; i < car_count - 1; i++) {
        for (size_t j = 0; j < car_count - 1 - i; j++) {
            if (cars[j].id > cars[j + 1].id) {
                Car temp = cars[j];
                cars[j] = cars[j + 1];
                cars[j + 1] = temp;
            }
        }
    }
}

void race_state(int *id, size_t size)
{
	if (size == 0)
	{
		free(cars);
		cars = NULL;
		car_count = 0;
		return;
	}

	for (size_t i = 0; i < size; i++)
	{
		int index = find_car(id[i]);
		if (index == -1)
		{
			add_car(id[i]);
		}
		else
		{
			cars[index].laps++;
		}
	}

	bubble_sort_cars();

	printf("\nRace state:\n");
	for (size_t i = 0; i < car_count; i++)
	{
		printf("Car %d [%d laps]\n", cars[i].id, cars[i].laps);
	}
}