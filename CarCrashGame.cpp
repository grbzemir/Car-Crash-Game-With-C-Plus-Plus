#include<iostream>
#include<Windows.h>
#include<thread> // Birden Fazla Arkaplanda Calistirilacak Islem Varsa Kullanilir
#include<stddef.h>


using namespace std;


#define satir 8
#define sutun 20

int matrix[satir][sutun];

void gotoxy(int x, int y) // gotoxy fonksiyonu ile imleci istedigimiz yere yönlendiriyoruz

{

    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

void drawPoint(int x, int y) // DrawPoint fonksiyonu ile noktalarimizi ciziyoruz

{

    if ( y < 20 && y>= 0)

    {

        matrix[x][y] = 1;
        
    }

}

void ekraniSil()

{

    int j;

    for ( j = 0; j < satir; j++)

    {
       
        int i;

        for ( i = 0; i < sutun; i++)

        {
            matrix[i][j] = 0;
            
        }
        
    }


}

class DusmanAraci

{
     
     public:
     int xPozisyonu;
     int yPozisyonu;

        DusmanAraci()
    
        {
    
            xPozisyonu = 5;
            yPozisyonu = -3; // Biraz daha asagiya cekelim
    
        }

        void AracimiCiz()

      {

       drawPoint(xPozisyonu, yPozisyonu );
       drawPoint(xPozisyonu-1, yPozisyonu+1 );
       drawPoint(xPozisyonu+1, yPozisyonu+1 );
       drawPoint(xPozisyonu, yPozisyonu+1);
       drawPoint(xPozisyonu, yPozisyonu+2 );
       drawPoint(xPozisyonu-1, yPozisyonu+3 );
       drawPoint(xPozisyonu, yPozisyonu+3 );
       drawPoint(xPozisyonu+1, yPozisyonu+3 );
        
      // DrwaPointde Çagırılan Bütün Şeyleri 1 Yaptık1



     }

    void Gozuksun()

    {

        if (yPozisyonu == 20)
        
        {
 
          int randomNumara = rand() % 2;

          if (randomNumara == 0)

          {

            xPozisyonu = 2;
            
          }

          else

          {

            xPozisyonu = 5;
             

          }

           yPozisyonu = -3;

        }


    }

        void HareketEttir()

        {

            yPozisyonu++;

        }


};


class BenimAracim

{

    public:

    int xPozisyonu;
    int yPozisyonu;

    BenimAracim()

    {

        xPozisyonu = 2;
        yPozisyonu = 16; // Biraz daha asagiya cekelim

    }

    void AracimiCiz()

    {

       drawPoint(xPozisyonu, yPozisyonu );
       drawPoint(xPozisyonu-1, yPozisyonu+1 );
       drawPoint(xPozisyonu+1, yPozisyonu+1 );
       drawPoint(xPozisyonu, yPozisyonu+1);
       drawPoint(xPozisyonu, yPozisyonu+2 );
       drawPoint(xPozisyonu-1, yPozisyonu+3 );
       drawPoint(xPozisyonu, yPozisyonu+3 );
       drawPoint(xPozisyonu+1, yPozisyonu+3 );
        
      // DrwaPointde Çagırılan Bütün Şeyleri 1 Yaptık1



    }

    void SolaGit()

    {

        xPozisyonu = 2;

    }

    void SagaGit()

    {

        yPozisyonu = 5;

    }

    void CarpismayiKontrolEt(DusmanAraci * arac,bool*running)

    {

        if (arac->xPozisyonu == xPozisyonu & arac->yPozisyonu > 13)

        {


            *running = false;

        }

       
    }



};


void AnahtarKontrol(BenimAracim * r)

{

    while ( true )

    {

     if (GetAsyncKeyState(VK_LEFT) & (0x8000!=0))

     {

        r->SolaGit();

     }


    if (GetAsyncKeyState(VK_RIGHT) & (0x8000!=0))

    {

        r->SagaGit();

    }

    
    }

}

 void MapiGetir()

 {
     
    BenimAracim  benimAracim = BenimAracim();
    DusmanAraci  dusmanAraci =  DusmanAraci();
    thread mThread(AnahtarKontrol, &benimAracim);

    bool isRunning = true;

    while(isRunning)

    {

        ekraniSil();
        dusmanAraci.Gozuksun();
        dusmanAraci.AracimiCiz();
        dusmanAraci.HareketEttir();

        benimAracim.AracimiCiz();
        benimAracim.CarpismayiKontrolEt(&dusmanAraci,&isRunning);

        int j;

    for ( j = 0; j < satir; j++)

    {
       
       int i;

        for ( i = 0; i < sutun; i++)

        {
            if( i == 0 || i==7)

            {
               
               gotoxy(i , j);
               cout<<"#";
                
            }

            else if (matrix[i][j] == 1)

            {
                gotoxy(i , j);
                cout<<"X";
                
            }

            else

            {
                gotoxy(i , j);
                cout<<" ";
                
            }

        }
        
    }

    Sleep(50);
       
    }

    system("cls");

    Sleep(1000);

    gotoxy(8 , 9);

    cout<<"Oyun Bitti";

    mThread.detach();
    
 }


int main()

{
    
    srand(time(NULL));
    MapiGetir();
    getchar();







    return 0;

}
