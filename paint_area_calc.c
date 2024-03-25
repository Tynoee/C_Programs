#include <stdio.h>
#include <stdlib.h>

struct Room {
    float length;
    float width;
    float height;
};

float calculateTotalWallArea(struct Room room) {
    float wallArea = 2 * (room.length * room.height + room.width * room.height);
    float ceilingArea = room.length * room.width;
    float floorArea = room.length * room.width;

    return wallArea + ceilingArea + floorArea;
}

int main() {
    struct Room myRoom;

    printf("Enter room length, width, and height: ");
    scanf("%f %f %f", &myRoom.length, &myRoom.width, &myRoom.height);

    float totalWallArea = calculateTotalWallArea(myRoom);


    printf("\nRoom Dimensions:\n");
    printf("Length: %.2f units\n", myRoom.length);
    printf("Width: %.2f units\n", myRoom.width);
    printf("Height: %.2f units\n", myRoom.height);
    printf("Total Wall Area for Painting: %.2f square units\n", totalWallArea);

    return 0;
}

