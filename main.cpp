#include <iostream>
#include <string>
using namespace std;

void numeric()
{
    string x;
    bool numeric = true;

    cout <<"Enter input: " ;
    cin>> x;

    for(int i=0; i<x.length();i++)
    {
        if (((int)x[i]<48 || (int)x[i]>57) && (int)x[i]!=46 )
        {
            numeric=false;
        }
    }

    if (numeric)
        cout<< "Numeric";
    else
        cout<<"Not Numeric";
}


void operators()
{
    string y;
    char op[]= {'+','-','*','/','%','='};
    string name[] = {"Addition","Subtraction","Multiplication","Division","Modulus","Assignment"};

    cout<< "Enter input: ";
    cin>> y;

    int count = 1;

    for (int i = 0; i < y.length(); i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (y[i] == op[j])
            {
                cout << "Operator" << count << ": "
                     << y[i] << "  " << name[j] << endl;

                count++;
            }
        }
    }
}


void comment()
{
    string x, line;

    cout << "Enter comment:\n";
    getline(cin, x);

    if (x[0] == '/' && x[1] == '/')
    {
        cout << "Single Line Comment";
    }
    else if (x[0] == '/' && x[1] == '*')
    {
        while (x[x.length() - 2] != '*' || x[x.length() - 1] != '/')
        {
            getline(cin, line);
            x = x + line;
        }

        cout << "Multiple Line Comment";
    }
    else
    {
        cout << "Not a Comment";
    }
}


void identifier()
{
    string x;
    bool valid = true;

    cout << "Enter Identifier: ";
    cin >> x;

    if (!((x[0] >= 65 && x[0] <= 90)||
          (x[0] >= 97 && x[0] <= 122)||
           x[0] == 95))
    {
        valid = false;
    }

    for (int i = 1; i < x.length(); i++)
    {
        if (!((x[i] >= 65 && x[i] <= 90) ||
              (x[i] >= 97 && x[i] <= 122)||
              (x[i] >= 48 && x[i] <= 57) ||
               x[i] == 95))
        {
            valid = false;
            break;
        }
    }

    if (valid)
        cout << "Identifier" << endl;
    else
        cout << "Not Identifier" << endl;
}


void average()
{
    int n;
    float sum = 0, avg;

    cout << "Enter number of elements: ";
    cin >> n;

    int arr[n];

    cout << "Enter array elements: ";

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        sum = sum + arr[i];
    }

    avg = sum / n;

    cout << "Average = " << avg << endl;
}


int main()
{
   numeric();

    operators();

    comment();

    identifier();

    average();

    return 0;
}
