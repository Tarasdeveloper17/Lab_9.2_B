#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>

using namespace std;

enum Specialnist { KN, IT, MATH_AND_ECON, PH_AND_INF, LABOR_TRAINING};
string specialnistStr[] = {"KN", "IT", "MATH_AND_ECON","PH_AND_INF", "LABOR_TRAINING"};

struct Student
{
    string surname;
    unsigned course;
    Specialnist specialnist;
    unsigned physics;
    unsigned math;
    union
    {
        unsigned prog;
        unsigned nMethods;
        unsigned pedagogy;
    };
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
void SortStudent(Student* p, const int N);
int *IndexSort(Student *p, const int N);
void PrintIndexSort(Student* p, int *I, const int N);
int BinSearch(Student *p, const int N,  const string surname, const  Specialnist specialnist,  const unsigned course);

int main() {
    cout<< "N :";
    int N;
    cin>>N;
    Student* p = new Student[N];
    Specialnist specialnist;
    int ispec;
    unsigned course;
    string surname;
    int found;
    int menuItem;
    
    do
    {
        cout << endl << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - Create info about student" << endl;
        cout << " [2] - Print info about student" << endl;
        cout << " [3] - Sort student " << endl << endl;
        cout << " [4] - IndexSort student " << endl << endl;
        cout << " [5] - PrintIndexSort student " << endl << endl;
        cout << " [6] - BinSearch student " << endl << endl;
        cout << " [0] - End program" << endl << endl;
        cout << "What you want: "; cin >> menuItem;
        cout << endl << endl << endl;
        
        switch (menuItem) {
            case 1:
                Create(p, N);
                break;
            case 2:
                Print(p, N);
                break;
            case 3:
                SortStudent(p, N);
                break;
            case 4:
                IndexSort(p, N);
                break;
            case 5:
                PrintIndexSort(p, IndexSort(p, N), N);
                break;
            case 6:
                cout << "Enter key:" << endl;
                cout << " Specialnist (0 - KN, 1 - IT, 2 - KIBERBEZPEKA, 3 - CA, 4 - RI):";
                cin >> ispec;
                specialnist = (Specialnist)ispec;
                cin.get();
                cin.sync();
                cout << " Surname : "; getline(cin, surname);
                cout<<endl;
                cout << " Course: "; cin >> course;
                 cout << endl;
                found = BinSearch(p, N, surname, specialnist, course);
                if (found != -1)
                    cout << "Found student  " << found+1 << endl;
                 else
                     cout << "NO Found" << endl;
                 break;
            case 0:
                break;
            default:
             cout << "Error! "
             "Enter a number - the number of the selected menu item" << endl;
        }
        
    } while(menuItem!=0);
    

    return 0;
}



void Create(Student* p, const int N)
{
    int specialnist;

    for (int i = 0; i < N; i++)
    {
        cout << "Student № " << i + 1 << ":" << endl;
        cin.get();
        cin.sync();
        cout << " Surname : "; getline(cin, p[i].surname);
        cout << " Course: "; cin >> p[i].course;
        cout << " Specialnist (0 - KN, 1 - IT, 2 - MATH_AND_ECON, 3 - PH_AND_INF, 4 - LABOR_TRAINING):";
        cin >> specialnist;
        cout << " Assessment in physics : "; cin >> p[i].physics;
        cout << "Assessment in math    : "; cin >> p[i].math;
        p[i].specialnist = Specialnist(specialnist);
        
        switch (p[i].specialnist) {
            case KN :
                cout<< "Third grade in programming: "; cin>>p[i].prog;
                break;
            case IT :
                cout<<"Third grade in numerical methods:"; cin>>p[i].nMethods;
                break;
            case MATH_AND_ECON:
            case PH_AND_INF:
            case LABOR_TRAINING:
                cout<<"Third grade in pedagogy: "; cin>>p[i].pedagogy;
                break;
                
        }
        cout << endl;
    }
}


void Print(Student* p, const int N)
{
    cout << "========================================================================================================"
        << endl;
    cout << "| № | Surname | Course | Spec | Score in PH | Score in MATH | Score in prog | Score in numerical methods | Score in pedagogy |"
        << endl;
    cout << "--------------------------------------------------------------------------------------------------------"
        << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(1) << right << i + 1 << " ";
        cout << "| " << setw(9) << left << p[i].surname
            << "| " << setw(4) << right << p[i].course << " "
            << "| " << setw(14) << left << specialnistStr[p[i].specialnist]
            << "| " << setw(6) << right << p[i].physics << " "
            << "| " << setw(10) << left << p[i].math << " ";
        switch (p[i].specialnist)
        {
        case KN:
            cout << "| " << setw(13) << right << p[i].prog << " " << "|" << setw(14) << "|" << setw(13) << "|";
            break;
        case IT:
            cout << "|" << setw(16) << right << fixed << "|" << setw(13) << left << p[i].nMethods << "|" << setw(11) << right << " " << " |";
            break;
        case MATH_AND_ECON:
        case PH_AND_INF:
        case LABOR_TRAINING:
            cout << "|" << setw(17) << right << fixed << "| " << setw(12) << left << " " << "| " << setw(11) << right << p[i].pedagogy << "|";
            break;
        }
        cout << endl;
    }
    cout << "=========================================================================================================="
        << endl;
    cout << endl;
}





void SortStudent(Student* p, const int N)
{
    Student temp;
    for(int i = 0; i < N-1; i++)
    {
        for(int j = 0; j < N-i-1; i++)
        {
            if((p[j].specialnist > p[j+1].specialnist) || (p[j].specialnist == p[j+1].specialnist && p[j].course > p[j+1].course) || (p[j].specialnist == p[j+1].specialnist && p[j].course == p[j+1].course && p[j].surname > p[j+1].surname))
            {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
                
            }
        }
    }
    
}


int *IndexSort(Student *p, const int N)
{
    int *I = new int[N];
    for (int i=0; i<N; i++)
        I[i]=i;
    int i, j, value;
    for (i = 1; i < N; i++)
    {
        value = I[i];
        for (j = i - 1;
             j >= 0 && ((p[I[j]].specialnist > p[value].specialnist ) ||
                        ( p[I[j]].specialnist == p[value].specialnist &&
                         p[I[j]].course > p[value].course) || (p[I[j]].specialnist == p[value].specialnist && p[I[j]].course == p[value].course && p[I[j]].surname > p[value].surname)) ;
             j--)
        {
            I[j + 1] = I[j];
        }
        I[j + 1] = value;
        
    }
    return I;
}
 


void PrintIndexSort(Student* p, int *I, const int N)
{
    cout << "=========================================================================="
        << endl;
    cout << "| № | Surname | Course | Spec | Score in PH | Score in MATH | Score in prog | Score in numerical methods | Score in pedagogy |"
        << endl;
    cout << "--------------------------------------------------------------------------"
        << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(1) << right << i + 1 << " ";
        cout << "| " << setw(10) << left << p[I[i]].surname
            << "| " << setw(2) << right << p[I[i]].course << " "
            << "| " << setw(15) << left << specialnistStr[p[I[i]].specialnist]
            << "| " << setw(6) << right << p[I[i]].physics << " "
            << "| " << setw(10) << left << p[I[i]].math << " "
            << "| " << setw(6) << right << p[I[i]].nMethods << " "
            << "| " << setw(6) << right << p[I[i]].prog << " "
            << "| " << setw(6) << right << p[I[i]].pedagogy << " ";
        cout << endl;
    }
    cout << "=========================================================================="
        << endl;
    cout << endl;
}
    
int BinSearch(Student *p, const int N,  const string surname, const  Specialnist specialnist,  const unsigned course)
{
    
 int L=0, R=N-1, m;
 do {
 m = (L+R)/2;
 if (p[m].surname == surname && p[m].specialnist == specialnist && p[m].course == course)
 {
     return m;
 }
 if ((p[m].specialnist < specialnist ) || (p[m].course < course) || (p[m].specialnist == specialnist && p[m].course == course && p[m].surname < surname))
 {
 L = m+1;
 }
 else
 {
 R = m-1;
 }
 } while ( L <= R );
    
 return -1;
    
}
