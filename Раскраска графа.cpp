//Для каждой вершины ввести сначала смежные с ней верщины, затем ввести 0
#include <iostream>
#define XRY 5 // Количество вершин графа.

using namespace std;

typedef struct zveno *svqz;
typedef struct zveno
{
    int Key;  // Вершина графа.
    svqz Up;  // Указатель на смежную вершину.
    svqz Sled;// Указатель на следующую смежную вершину.
};

class List
{
private:
    svqz Beg[XRY+1]; //Массив указателей на вершины.
    void Add_Ver (int);
    int Find (int, int, svqz *);
    void Add_duga (int, int);
    void Make (int, int);
    int Find_Color (int, int, svqz *);
public:
    List();
    void Init_Graph ();
    void Make_Graph ();
    void Print_Graph ();
    void Color ();
    void Print_Color ();
};

int main ()
{
    List A;
    //Инициализация графа.
    A.Init_Graph ();
    //Построение графа.
    A.Make_Graph ();
    //Вывод графа.
    A.Print_Graph ();
    //Последовательная раскраска графа, представленного
    //модифицированными списками смежности.
    A.Color ();
    A.Print_Color ();
    return 0;
}

List::List()
{
    for ( int i=0; i<=XRY;Beg[i++] = NULL );
}

void List::Add_Ver (int x)
//Функция создания вершины x.
{
    svqz Ukaz = new (zveno);

    Ukaz->Sled = NULL;
    Beg[x] = Ukaz;
}

void List::Init_Graph ()
//Функция инициализации модифицированных списков смежности.
{
    for (int i=1;i<=XRY;i++) Add_Ver (i);
}

int List::Find (int x, int y, svqz *UkZv)
//Функция проверки смежности вершин y и x. Функция возвращает
//TRUE, если  вершина x смежна с вершиной y. Указатель *UkZv,
//возвращает указатель на место y в списке  смежности x. Если
//вершина x не смежна с вершиной y, то UkZv есть NULL.
{
    svqz Ukaz;

    Ukaz = Beg[x]->Sled;
    while  (Ukaz != NULL && Ukaz->Key != y)
        Ukaz = Ukaz->Sled;
    *UkZv = Ukaz;
    return  ( Ukaz != NULL );
}

void List::Add_duga (int x, int y)
//Функция создания дуги (x,y).
{
    svqz Ukaz = new (zveno);

    Ukaz->Sled = Beg[x]->Sled; Ukaz->Key = y;
    Beg[x]->Sled = Ukaz;
}

void List::Make (int x, int y)
//Функция создания ребра {x,y}.
{
    svqz Ukaz;

    if  ( !Find(x,y,&Ukaz) )
    {
        Add_duga (x,y);
        if ( x != y ) Add_duga (y,x);
        Beg[x]->Sled->Up = Beg[y];
        Beg[y]->Sled->Up = Beg[x];
    }
}

void List::Make_Graph ()
//Функция построения модифицированных списков смежности.
{
    int f;

    for (int i=1;i<=XRY;i++)
    {
        cout << "Enter tops adjacent to  " << i << " top" << endl;
        cin >> f;
        while (f!=0)
        {
            Make (i,f);
            cout << " ";
            cin >> f;
        }
        cout << endl;
    }
}

void List::Print_Graph ()
//Функция вывода содеpжимого модифицированных
//списков смежности.
{
    svqz UkZv;

    for (int i=1;i<=XRY;i++)
    {
        if ( Beg[i] != NULL )
        {
            UkZv = Beg[i]->Sled;
            cout << i << " - ";
            while ( UkZv != NULL )
            {
                cout << " " << UkZv->Key;
                UkZv = UkZv->Sled;
            }
        }
        cout << endl;
    }
}

int List::Find_Color (int x, int c, svqz *UkZv)
//Функция  выявления возможности раскраски вершины  x цветом c.
//Функция  возвращает TRUE, если вершину  x  можно  раскрасить.
//Указатель *UkZv, возвращает указатель на вершину, смежную с x
//и раскрашенную цветом c. Если вершину x можно раскрасить, то
//*UkZv есть NULL.
{
    int i = 1;

    while (!(Find(x,i,&(*UkZv)) &&
             Beg[i]->Key==c)   &&
           i != x) i++;
    return (i==x);
}

void List::Color ()
//Функция последовательной раскраски графа, заданного
//модифицированными списками смежности Beg.
{
    int i = 1;
    int c = 1;
    svqz UkZv;

    while  (Beg[i] == NULL && i<=XRY) i++;
    if ( i != XRY )
    {
        Beg[i]->Key = c;
        i++;
        while  (i<=XRY)
            if ( Beg[i] != NULL )
            {
                c = 1;
                while  (!Find_Color(i,c,&UkZv)) c++;
                Beg[i]->Key = c; i++;
            }
            else  i++;
    }
    else  cout << "Graph is absent";
}

void List::Print_Color ()
//Функция вывода раскраски графа, заданного
//модифицированными списками смежности Beg.
{
    for (int i=1;i<=XRY;i++)
        //if ( Beg[i] != NULL )
            cout << " Color  of " << i << " top is " << Beg[i]->Key << endl;
}