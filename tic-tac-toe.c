#include<stdio.h>
#include<stdlib.h>
#include<windows.h> // For windows
// #include<sys/ioctl.h> // For linux
#include<unistd.h>

//This Function used for linux
// int get_col()
// {
//     struct winsize w;
//     ioctl(STDOUT_FILENO,TIOCGWINSZ,&w);
//     return w.ws_col;
// }

// This Function Used for windows
int get_col() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;

    // Get the handle to the standard output
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    // Get console screen buffer info
    if (GetConsoleScreenBufferInfo(hStdout, &csbi)) {
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    } else {
        columns = -1; // Error case
    }

    return columns;
}
void init_mat_value(char matrix[3][3])
{
    char num,i,j;
    num ='1';
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            matrix[i][j]=num;
            num++;
        }
    }
    
}
void box_print(int column)
{
    int i,j;
    char num;
    // system("clear");
    system("cls");
    printf("\e[1;%dH",(column-21)/2);
    printf("\e[32m\e[1m~~\e[38;5;14m\e[4mTic-Tac-Toe Game\e[0m\e[32m~~\n\e[0m");
    for(i=1; i<=7; i++)
        {
            for(j = 1; j<(column - 21)/2; j++)
            {
                printf(" ");
            }

            if(i%2 != 0)
            {
                for(j=1; j<=21; j++)
                {
                    printf("=");
                }
            }
            else
            {
                for(j=1; j<=21; j++)
                {
                    num ='1';

                    if((i>1 && i<7)&&(j==7 || j==14 || j==1 || j==21))
                    {
                        printf("|");
                        continue;
                    }
                    printf(" ");
                }
            }
            printf("\n");
        }
    
}
void value_putting(char matrix[3][3],int posi[3][3])
{
    int i,j,k;
     for(i=0,k=3; i<3&&k<9; i++,k=k+2)
        {
            for(j=0; j<3; j++)
            {
                printf("\e[%d;%dH",k,posi[i][j]);
                if(matrix[i][j] >= '1' && matrix[i][j] <='9')
                {
                    printf("\e[38;5;127m%c\e[0m",matrix[i][j]);
                }
                else if(matrix[i][j]=='P')
                {
                    printf("\e[31m\e[41m%c\e[0m",matrix[i][j]);
                }
                else
                {
                    printf("\e[38;5;3m%c\e[0m",matrix[i][j]);
                }
            }

        }
    
}
int quit_game()
{
    char quit;
    printf("\n\e[31mAre you want to quit Game ?(Y/N,default = N): \e[0m");
   scanf("%c",&quit);
   while(getchar() != '\n');
   if(quit == 'Y' || quit =='y')
   {
       return 1;
   }
   else
   {
       return 0;
   }
                    
}
int main()
{
    int column,i,j,k,num,posi[3][3],count,game_continue;
    char matrix[3][3],x,o;
    // Getting Column size
    start :
    count =1;
    // system("clear"); // For linux
    system("cls"); // For Windows
    column = get_col();
    // Initial Matrix value 1 to 9
    init_mat_value(matrix);
    //Intial position of value
    for(i = 0; i<3; i++)
    {
        posi[i][0] = ((column-21)/2) +3;
        posi[i][1] = ((column-21)/2) +10;
        posi[i][2] =  ((column-21)/2) +17;
    }
    while(1)
    {
        // Tic-Tac-Toe Box printing
        box_print(column);
        // Value putting in box
        value_putting(matrix,posi);
        //***Game start***
        // Getting input of position
        printf("\e[9;0H");
        while(1)
        {
            for(j = 1; j<(column - 21)/2; j++)
            {
                printf(" ");
            }
            //For O
            if(count ==1)
            {
                printf("\e[38;5;10mPlayer 1 :\e[0mPosition of [ O ] : ");
                scanf("%c",&o);
                if(o >= '1' && o<='9')
                {
                    if((o-'0') <= 3)
                    {
                        // Checking , Is value already aviable in this position ? if not then assign O .
                        if(matrix[0][(o-'0')-1] == 'O' || matrix[0][(o-'0')-1] == 'X')
                        {
                            while(getchar() != '\n');
                            printf("\e[31m Error :\e[0m\n");
                        }
                        else
                        {
                           matrix[0][(o-'0')-1] = 'O' ; 
                           count++;
                           break;
                        }
                    }
                    else if((o-'0') > 3 && (o-'0') <= 6)
                    {
                        if(matrix[1][(o-'0')-4] == 'O' || matrix[1][(o-'0')-4] == 'X')
                        {
                            while(getchar() != '\n');
                            printf("\e[31m Error :\e[0m\n");
                        }
                        else
                        {
                           matrix[1][(o-'0')-4] = 'O' ; 
                           count++;
                           break;
                        }
                    }
                    else if((o-'0') >6 && (o-'0') <=9)
                    {
                       if(matrix[2][(o-'0')-7] == 'O' || matrix[2][(o-'0')-7] == 'X')
                        {
                            while(getchar() != '\n');
                            printf("\e[31m Error :\e[0m\n");
                        }
                        else
                        {
                           matrix[2][(o-'0')-7] = 'O' ; 
                           count++;
                           break;
                        }
                    }
                }
                else
                {
                    while(getchar() != '\n');
                    printf("\e[31m Error :\e[0m\n");
                }
            }
            //For X 
            else if(count == 2 )
            {
                printf("\e[38;5;10mPlayer 2 :\e[0m Position of [ X ] :");
                scanf("%c",&x);
                if(x>= '1' && x<='9')
                {
                     // Checking , Is value already aviable in this position ? if not then assign X .
                
                    if((x-'0') <= 3)
                    {
                       if(matrix[0][(x-'0')-1] == 'O' || matrix[0][(x-'0')-1] == 'X')
                        {
                            while(getchar() != '\n');
                            printf("\e[31m Error :\e[0m\n");
                        }
                        else
                        {
                           matrix[0][(x-'0')-1] = 'X' ; 
                           count =1;
                           break;
                        }
            
                    }
                    else if((x-'0') > 3 && (x-'0') <= 6)
                    {
                        if(matrix[1][(x-'0')-4] == 'O' || matrix[1][(x-'0')-4] == 'X')
                        {
                            while(getchar() != '\n');
                            printf("\e[31m Error :\e[0m\n");
                        }
                        else
                        {
                           matrix[1][(x-'0')-4] = 'X' ; 
                           count =1;
                           break;
                        }
                    }
                    else if((x-'0') >6 && (x-'0') <=9)
                    {
                       if(matrix[2][(x-'0')-7] == 'O' || matrix[2][(x-'0')-7] == 'X')
                        {
                            while(getchar() != '\n');
                            printf("\e[31m Error :\e[0m\n");
                        }
                        else
                        {
                           matrix[2][(x-'0')-7] = 'X' ; 
                           count =1;
                           break;
                        }
                    }
                }
                else
                {
                    while(getchar() != '\n');
                    printf("\e[31m Error :\e[0m\n");
                }
            }
        }
       getchar();
        //Game Over 
        for(i=0;i<3;i++)
        {
            if(matrix[i][0] == matrix[i][1] && matrix[i][0] == matrix[i][2])
            {
                
                if(matrix[i][0] == 'O')
                {
                    
                    matrix[i][0]='P';
                    matrix[i][1]='P';
                    matrix[i][2]='P';
                    box_print(column);
                    value_putting(matrix,posi);
                    printf("\e[9;%dH",(column-21)/2);
                    printf("\e[1m\e[38;5;201m PLAYER 1 IS WINNER\e[0m");
                    
                    if(quit_game())
                    {
                        return 0;
                    }
                    else
                    {
                        goto start;
                    }
                }
                else if(matrix[i][0] == 'X')
                {
                    
                    matrix[i][0]='P';
                    matrix[i][1]='P';
                    matrix[i][2]='P';
                    box_print(column);
                    value_putting(matrix,posi);
                    printf("\e[9;%dH",(column-21)/2);
                    printf("\e[1m\e[38;5;201m PLAYER 2 IS WINNER\e[0m");
                    if(quit_game())
                    {
                        return 0;
                    }
                    else
                    {
                        goto start;
                    }
                }
            }
        }
        for(i=0;i<3;i++)
        {
            if(matrix[0][i] == matrix[1][i] && matrix[0][i] == matrix[2][i])
            {
                
                if(matrix[0][i] == 'O')
                {
                    
                    matrix[0][i]='P';
                    matrix[1][i]='P';
                    matrix[2][i]='P';
                    box_print(column);
                    value_putting(matrix,posi);
                    printf("\e[9;%dH",(column-21)/2);
                    printf("\e[1m\e[38;5;201m PLAYER 1 IS WINNER\e[0m");
                    if(quit_game())
                    {
                       return 0;
                    }
                    else
                    {
                         goto start;
                    }
                }
                else if(matrix[0][i] == 'X')
                {
                    
                    matrix[0][i]='P';
                    matrix[1][i]='P';
                    matrix[2][i]='P';
                    box_print(column);
                    value_putting(matrix,posi);
                    printf("\e[9;%dH",(column-21)/2);
                    printf("\e[1m\e[38;5;201m PLAYER 2 IS WINNER\e[0m");
                    if(quit_game())
                    {
                        return 0;
                    }
                    else
                    {
                         goto start;
                    }
                }
            }
        }
        if((matrix[0][2] == matrix[1][1] && matrix[0][2] == matrix[2][0]) ||(matrix[0][0] == matrix[1][1] && matrix[0][0] == matrix[2][2]))
        {
              // For O
              if((matrix[0][2] == 'O' && matrix[1][1] == 'O' && matrix[2][0] == 'O') ||(matrix[0][0] == 'O' && matrix[1][1] == 'O' && matrix[2][2] == 'O') )
                {
                    if(matrix[0][2]=='O' && matrix[1][1] =='O'&& matrix[2][0] == 'O')
                    {
                        
                        matrix[0][2]='P';
                        matrix[1][1]='P';
                        matrix[2][0]='P';
                        box_print(column);
                        value_putting(matrix,posi);
                    }
                    else if(matrix[0][0] == 'O' && matrix[1][1] == 'O' && matrix[2][2] == 'O')
                    {
                        
                        matrix[0][0]='P';
                        matrix[1][1]='P';
                        matrix[2][2]='P';
                        box_print(column);
                        value_putting(matrix,posi);
                    }
                    printf("\e[9;%dH",(column-21)/2);
                    printf("\e[1m\e[38;5;201m PLAYER 1 IS WINNER\e[0m");
                    if(quit_game())
                    {
                       return 0;
                    }
                    else
                    {
                         goto start;
                    }
                }
                // For X
                else 
                {
                     if(matrix[0][2]=='X' && matrix[1][1] =='X'&& matrix[2][0] == 'X')
                    {
                        matrix[2][0]='P';
                        matrix[1][1]='P';
                        matrix[0][2]='P';
                        box_print(column);
                        value_putting(matrix,posi);
                    }
                    else if(matrix[0][0] == 'X' && matrix[1][1] == 'X' && matrix[2][2] == 'X')
                    {
                        
                        matrix[0][0]='P';
                        matrix[1][1]='P';
                        matrix[2][2]='P';
                        box_print(column);
                        value_putting(matrix,posi);
                    }
                    printf("\e[9;%dH",(column-21)/2);
                    printf("\e[1m\e[38;5;201m PLAYER 2 IS WINNER\e[0m");
                    if(quit_game())
                    {
                        return 0;
                    }
                    else
                    {
                         goto start;
                    }
                }
            }
         for(i=0;i<3;i++)
         {
             for(j=0;j<3;j++)
             {
                 if(matrix[i][j] >= '1' && matrix[i][j] <= '9')
                 {
                     game_continue = 1;
                     goto match_draw;
                 }
                 else
                 {
                     game_continue =0;
                 }
             }
          }
          match_draw:
          if(game_continue)
          {
              continue;
          }
          else
          {
               box_print(column);
               value_putting(matrix,posi);
               printf("\e[9;%dH",(column-21)/2);
               printf("\e[1m\e[38;5;201m     Match Draw\e[0m");
                    if(quit_game())
                    {
                        return 0;
                    }
                    else
                    {
                         goto start;
                    }
          }

    }
    return 0;
}
