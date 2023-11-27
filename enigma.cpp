#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


class Enigma
{
private:
    int psrn;
    string rotor1;
    string rotor2;
    string rotor3;
public:
    Enigma(const int _psrn, const string _r1, const string _r2, const string _r3): psrn(_psrn), rotor1(_r1), rotor2(_r2), rotor3(_r3) {}

    int getPos(const char letter) const;
    int getPos(const char letter, const string rotor) const;

    int getShift(const char letter, int current_shift) const;

    void encode(string *message) const;
    void decode(string *message) const;

    void print() const 
    {
        cout << "pseudo rundom nuber (shift):\t" << psrn 
        << "\nfirst rotor:\t\t\t" << rotor1 << "\nsecond rotor:\t\t\t" << rotor2 << "\nthird rotor:\t\t\t" << rotor3 << endl;
    }
};



int main()
{
    ifstream input;
    input.open("input.txt");

    string operation;
    getline(input, operation);

    int psrn;
    input >> psrn; input.ignore();

    vector<string> rotors(3);
    for (int i = 0; i < 3; i++) {
        string rotor;
        getline(input, rotor);

        rotors[i] = rotor;
    }
    string message;
    getline(input, message);
    Enigma enigma(psrn, rotors[0], rotors[1], rotors[2]);
    // enigma.print();

    if(operation == "ENCODE")
    {   
        cout << "encoding: " << message << endl;
        enigma.encode(&message);
    }
    else
    {
        cout << "decoding: " << message << endl;
        enigma.decode(&message);
    }
    cout << "result: "  << message << endl;

    input.close();
    return 0;
}



int Enigma::getPos(const char letter) const
{
    const string alphabebet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int i = 0; i < 26; i++) if(letter == alphabebet[i]) return i;
    return -1;
}
int Enigma::getPos(const char letter, const string rotor) const
{
    for(int i = 0; i < 26; i++) if(letter == rotor[i]) return i;
    return -1;
}

int Enigma::getShift(const char letter, int current_shift) const
{
    if(current_shift >= 0)
    {
        //A
        while(current_shift > 25) current_shift-=26;
        //Z
        if(letter + current_shift > 'Z') current_shift -= 26; 

        return current_shift;
    }
    else
    {
        //Z
        while(current_shift < -26) current_shift+=26;
        //A
        if(letter + current_shift < 'A') current_shift += 26;
        return current_shift;
    }
}

void Enigma::encode(string *message) const
{
    for(int i = 0; i < message->length(); i++)
    {   
        (*message)[i] += getShift( (*message)[i] ,psrn + i);       
        (*message)[i] = rotor1[ getPos( (*message)[i] ) ];     
        (*message)[i] = rotor2[ getPos( (*message)[i] ) ];
        (*message)[i] = rotor3[ getPos( (*message)[i] ) ];

    }
}
void Enigma::decode(string *message) const 
{
    const string alphabebet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int i = 0; i < message->length(); i++)
    {
        (*message)[i] = alphabebet[ getPos( (*message)[i], rotor3 ) ];
        (*message)[i] = alphabebet[ getPos( (*message)[i], rotor2 ) ];
        (*message)[i] = alphabebet[ getPos( (*message)[i], rotor1 ) ];
        (*message)[i] += getShift( (*message)[i], -1*(psrn + i) );
    }
}