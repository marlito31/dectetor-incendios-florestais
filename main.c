#include <stdio.h>
#include <stdlib.h>

#define SMALL_GRID 3
#define WHOLE_GRID 10

void printCharGreenBg(char character)
{
    printf("\033[42m %c \033[m", character);
}

typedef struct Sensor
{
    int id;
    char matrix[SMALL_GRID][SMALL_GRID];
    int posX, posY;
} Sensor;

Sensor *initiateSensor(int id, int positionX, int positionY)
{
    Sensor *sensor = malloc(sizeof(Sensor));
    if (sensor == NULL)
    {
        fprintf(stderr, "Memory allocation of sensor id: %d failed\n", id);
        return NULL;
    }
    sensor->id = id;
    sensor->posX = positionX;
    sensor->posY = positionY;
    for (int i = 0; i < SMALL_GRID; i++)
    {
        for (int j = 0; j < SMALL_GRID; j++)
        {
            if (i == 1 && j == 1)
            {
                sensor->matrix[i][j] = 'T';
            }
            else
            {
                sensor->matrix[i][j] = '-';
            }
        }
    }
    return sensor;
}

void printSensor(Sensor *sensor)
{
    for (int i = 0; i < SMALL_GRID; i++)
    {
        for (int j = 0; j < SMALL_GRID; j++)
        {
            printCharGreenBg(sensor->matrix[i][j]);
        }
        printf("\n");
    }
}

Sensor initiateGrid(Sensor *grid[WHOLE_GRID][WHOLE_GRID])
{
    int id = 0;
    for (size_t i = 0; i < WHOLE_GRID; i++)
    {
        for (size_t j = 0; j < WHOLE_GRID; j++)
        {
            id++;
            grid[i][j] = initiateSensor(id, i, j);
        }
    }
}

void freeGrid(Sensor *grid[WHOLE_GRID][WHOLE_GRID])
{
    for (size_t i = 0; i < WHOLE_GRID; i++)
    {
        for (size_t j = 0; j < WHOLE_GRID; j++)
        {
            free(grid[i][j]);
        }
    }
}

void printSensorGrid(Sensor *grid[WHOLE_GRID][WHOLE_GRID])
{
    size_t iIdx = 0, jIdx = 0;
    // printing horizontal coordinates to better visualization
    printf("%5s", ""); // 5 was chosen because the rows are formatted as %4ld and the first is always zero
    for (jIdx; jIdx < SMALL_GRID * WHOLE_GRID; jIdx++)
        printf("%2ld ", jIdx);
    printf("\n");

    for (size_t j = 0; j < WHOLE_GRID; j++)
    {
        for (size_t jSensor = 0; jSensor < SMALL_GRID; jSensor++)
        {
            for (size_t i = 0; i < WHOLE_GRID; i++)
            {
                // printing vertical coordinates to better visualization
                if (i == 0)
                    printf("%4ld ", iIdx++);
                for (size_t iSensor = 0; iSensor < SMALL_GRID; iSensor++)
                    printCharGreenBg(grid[i][j]->matrix[iSensor][jSensor]);
            }
            printf("\n");
        }
    }
}

int main(int argc, char const *argv[])
{
    Sensor *sensors[WHOLE_GRID][WHOLE_GRID];
    initiateGrid(sensors);

    printSensorGrid(sensors);

    freeGrid(sensors);
    return 0;
}
