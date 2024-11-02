#include <stdio.h>
#include <conio.h>

//map
//b = blank, u = unmovableWall, w = wall, o = objective, O = objective variant2, k = key, p = player, t = trap
//T = different interval trap, ? = wall on trap, m = monster, s = just spike
//6 9
#define row 3
#define collumn 3
/*char map[row][collumn] = {
        {'u', 'u', 'b', 'b', 'b', 'b', 'b', 'u', 'u'},
        {'u', 'u', 'u', 'w', 'o', 'w', 'u', 'u', 'u'},
        {'u', 'w', 'u', 'w', 'b', 'b', 'u', 'b', 'u'},
        {'w', 'b', 'w', 'w', 'w', 'w', 'b', 'b', 'k'},
        {'b', 'w', 'b', 'b', 'b', 'w', 'w', 'w', 'b'},
        {'u', 'b', 'b', 'w', 'b', 'b', 'b', 'w', 'u'}
    };*/
    char map[row][collumn] = {
        {'w', 'm', 's'},
        {'b', 'b', 'b'},
        {'b', 'w', 'b'}
    };

int checkNext(int px, int py, char map[row][collumn], int x, int y) {
    //wall case
    char temp;
    if (map[py + y][px + x] == 'w'){
        //push wall
        if(map[py + (2 * y)][px + (2 * x)] == 'b'  && px + (2 * x) >= 0 && px + (2 * x) < collumn) {
            printf(" %c",map[py + (2 * y)][px + (2 * x)]);
            temp = map[py + (2 * y)][px + (2 * x)];
            map[py + (2 * y)][px + (2 * x)] = map[py + y][px + x];
            map[py + y][px + x] = temp;
        }
        //push wall over trap
        else if(map[py + (2 * y)][px + (2 * x)] == 't'  && px + (2 * x) >= 0 && px + (2 * x) < collumn){
            map[py + (2 * y)][px + (2 * x)] = '?';
            map[py + y][px + x] = 'b';
        }
        else if(map[py + (2 * y)][px + (2 * x)] == 'T'  && px + (2 * x) >= 0 && px + (2 * x) < collumn){
            map[py + (2 * y)][px + (2 * x)] = '?2';
            map[py + y][px + x] = 'b';
        }
        else if(map[py + (2 * y)][px + (2 * x)] == 's'  && px + (2 * x) >= 0 && px + (2 * x) < collumn){
            map[py + (2 * y)][px + (2 * x)] = '?3';
            map[py + y][px + x] = 'b';
        }
    return -1;
    }
    //wall on trap case
    if (map[py + y][px + x] == '?'){
        if(map[py + (2 * y)][px + (2 * x)] == 'b'  && px + (2 * x) >= 0 && px + (2 * x) < collumn) {
            map[py + (2 * y)][px + (2 * x)] = 'w';
            map[py + y][px + x] = 't';
        }
        else if(map[py + (2 * y)][px + (2 * x)] == 't'  && px + (2 * x) >= 0 && px + (2 * x) < collumn){
            map[py + (2 * y)][px + (2 * x)] = '?';
            map[py + y][px + x] = 't';
        }
    return -1;
    }
    //unmovable wall case
    else if(map[py + y][px + x] == 'u'){
        return -1;
    }
    //key case
    else if(map[py + y][px + x] == 'k'){
        map[py + y][px + x] = 'b';
        return 1;
    }
    //objective case
    else if(map[py + y][px + x] == 'o'){
        return 2;
    }
    //monster case
    else if(map[py + y][px + x] == 'm'){
        //push monster
        if(map[py + (2 * y)][px + (2 * x)] == 'b'  && px + (2 * x) >= 0 && px + (2 * x) < collumn) {
            printf(" %c",map[py + (2 * y)][px + (2 * x)]);
            temp = map[py + (2 * y)][px + (2 * x)];
            map[py + (2 * y)][px + (2 * x)] = map[py + y][px + x];
            map[py + y][px + x] = temp;
        }
        //push monster over trap
        else if(map[py + (2 * y)][px + (2 * x)] == 't'  && px + (2 * x) >= 0 && px + (2 * x) < collumn){
            map[py + (2 * y)][px + (2 * x)] = 'M';
            map[py + y][px + x] = 'b';
        }
        //push monster aganist wall
        else if(map[py + (2 * y)][px + (2 * x)] == 'w'  && px + (2 * x) >= 0 && px + (2 * x) < collumn){
            map[py + y][px + x] = 'b';
        }
        //push monster aganist unmovableWall
        else if(map[py + (2 * y)][px + (2 * x)] == 'u'  && px + (2 * x) >= 0 && px + (2 * x) < collumn){
            map[py + y][px + x] = 'b';
        }
    return -1;
    }
    return 0;  // Indicate no move was made
}

int checkInteraction(int playerX, int playerY) {
    // Check if player is next to the demon
    if ((map[playerY][playerX + 1] == 'O') || (map[playerY][playerX - 1] == 'O') ||
        (map[playerY + 1][playerX] == 'O') || (map[playerY - 1][playerX] == 'O')) {
        printf("\nYou have encountered a demon! Initiating interaction...\n");
        // Trigger interaction logic here (e.g., dialogue or puzzle)
        victory();
        return 1;
    }
}

void victory(){
    printf("\n\n\nYou win!!!");
}

void youLose(){
    printf("\n\n\nYou lose!!!");
}

int main()
{
    int turn = 23,Rturn = turn;
    //5 5
    int playerX = 1,playerY = 1,key = 0;
    while(1){
        printf("turn left : %d\n",turn);
        //generate map
        printf("%d,%d\n",playerX,playerY);
        for(int i=0;i<row;i++){
            for(int j=0;j<collumn;j++){
                if(j == playerX && i == playerY){
                    printf("@ ");
                }
                else if(map[i][j] == 't'){
                    if((Rturn % 2) == 0){
                        printf("t ");
                    }
                    else{
                        printf("# ");
                    }

                }
                else if(map[i][j] == 'T'){
                    if((Rturn % 2) != 0){
                        printf("T ");
                    }
                    else{
                        printf("# ");
                    }

                }
                else if(map[i][j] == 'b'){
                    printf("  ");
                }
                else if(map[i][j] == 's'){
                    printf("s ");
                }
                else if(map[i][j] == 'm'){
                    printf("m ");
                }
                else if(map[i][j] == 'O'){
                    printf("O ");
                }
                else if(map[i][j] == '?'){
                    printf("? ");
                }
                else if(map[i][j] == 'o'){
                    printf("o ");
                }
                else if(map[i][j] == 'k'){
                    printf("k ");
                }
                else if(map[i][j] == 'w'){
                    printf("w ");
                }
                else if(map[i][j] == 'u'){
                    printf("u ");
                }

            }
            printf("\n");
        }
        if(turn <= 0){
            youLose();
            break;
        }
        printf("Enter movement direction(W,A,S,D): ");

        //move
        char direction,temp;
        int result;
        direction = getch();
        if(direction == 'w'){
            if(playerY-1 >= 0){
                result = checkNext(playerX,playerY,map,0,-1);
                if(result == 0){
                    playerY -= 1;
                }
                else if(result == 1){
                    playerY -= 1;
                    key = 1;
                }
            }
        }
        else if(direction == 's'){
            if(playerY+1 < row){
                result = checkNext(playerX,playerY,map,0,1);
                if(result == 0){
                    playerY += 1;
                }
                else if(result == 1){
                    playerY += 1;
                    key = 1;
                }
            }
        }
        else if(direction == 'a'){
            if(playerX-1 >= 0){
                result = checkNext(playerX,playerY,map,-1,0);
                if(result == 0){
                    playerX -= 1;
                }
                else if(result == 1){
                    playerX -= 1;
                    key = 1;
                }
            }
        }
        else if(direction == 'd'){
            if(playerX+1 < collumn){
                result =  checkNext(playerX,playerY,map,1,0);
                if(result == 0){
                    playerX += 1;
                }
                else if(result == 1){
                    playerX += 1;
                    key = 1;
                }
            }
        }
        //check turn end conditions
        if(result == 2 && key == 1){
            victory();
            break;
        }
        else if(map[playerY][playerX] == 't'){
            if((Rturn % 2) != 0){
                turn--;
            }
        }
        else if(map[playerY][playerX] == 't'){
            if((Rturn % 2) == 0){
                turn--;
            }
        }
        else if(map[playerY][playerX] == 's'){
            turn--;
        }
         if(checkInteraction(playerX, playerY) == 1){
            break;
         }
        turn--;
        Rturn--;
    }
}
