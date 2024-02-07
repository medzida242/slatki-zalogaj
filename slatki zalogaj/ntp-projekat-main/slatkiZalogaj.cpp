#include<iostream>
#include<iomanip>
#include<string>
#include<algorithm>
#include <time.h> 
#include<fstream>
#include<vector>
using namespace std;

//Enumeracija
enum vrstaPoslastice { Palacinka = 1, Kolac};

//Struktura Poslastice
struct Poslastica{
	string nazivPoslastice;
	vrstaPoslastice vrsta;
	float cijena;
};

//Struktura kupca
struct Kupac {
	string ime;
	string prezime;
	string spol;
	string adresa;
};

//Vektor za spremanje artikala
vector<Poslastica> poslastica;
vector<Kupac>kupci;

//Definisanje menija radi ukljucenosti u druge funkcije
void adminMeni();

//Funkcija za unos kupca
void unosKupca() {
		Kupac k;
		cin.ignore();
		cout << "\t\t\t\t    Ime: ";
		getline(cin, k.ime);
		cout << endl;
		cout << "\t\t\t\t    Prezime: ";
		getline(cin, k.prezime);
		cout << endl;
		cout << "\t\t\t\t    Spol [ Z ili M ]: ";
		cin >> k.spol;
		while (k.spol != "Z" && k.spol != "z" && k.spol != "M" && k.spol != "m") {
			if (cin.fail()) {
				cin.clear();
				cin.ignore();
				cout << "\t\t\t\t    Pogresan unos...\n ";
				cout << "\t\t\t\t    Unijeli ste broj, a unos je u obliku slova.\n";
				cout << "\n\t\t\t\t    Molimo ponovo unesite spol: ";
			}

			else {
				cout << "\t\t\t\t    Pogresan unos...\n ";
				cout << "\t\t\t\t    Unijeli ste pogresno slovo.\n";
				cout << "\n\t\t\t\t    Molimo ponovo unesite spol: ";
			}
			cin >> k.spol;
		}
		cout << endl;
		cin.ignore();
		cout << "\t\t\t\t    Adresa: ";
		getline(cin, k.adresa);
		cout << endl;
		kupci.push_back(k);
}

//Unos Recepta u .txt dokumentu
void dodajRecept(string naslov, string upute){
	ofstream Recept("Recepti.txt", ios::app);
	Recept << endl;
	Recept << "\t\t\t\t\t\t\t\tNaslov: " << naslov << endl;
	Recept << "\t\t\t\t\t\t\t\tUpute: "<<upute<<endl;
	Recept.close();
}
//Dodavanje artikla u vektor svih artikala
void dodajArtikal(string naziv, int cijena,vrstaPoslastice vrsta){
	Poslastica p;
	p.nazivPoslastice=naziv;
	p.cijena=cijena;
	p.vrsta=vrsta;
	poslastica.push_back(p);
	adminMeni();
}

//admin Opcije
void adminMeni(){
	cout<<"			I---------------------------------I "<<endl;
	cout<<"			I                                 I "<<endl;
	cout<<"			I                                 I "<<endl;
	cout<<"			I         Welcome back !!!        I "<<endl;
	cout<<"			I                                 I "<<endl;
	cout<<"			I                                 I "<<endl;
	cout<<"			I                                 I "<<endl;
	cout<<"			I---------------------------------I "<<endl;
	int adminOdabir;
	cout<<"\t\t Odaberite opcije: " <<endl;
	cout<<"\t\t 1.Dodaj recept " <<endl;
	cout<<"\t\t 2.Dodaj artikal " <<endl;
	cout<<"\t\t 3.Povratak na meni " <<endl;
	cout<<"\t\t Pregled svih kupaca " <<endl;
	cin>>adminOdabir;
	
		//Unos Recepata u dokument pomocu funkcije, takoder rekurzivna funkcija
	if(adminOdabir==1){
		string naslov;
		cout<<"Unesite naslov recepta: ";
		cin.ignore();
		getline(cin , naslov);
		string upute;
		cout<<"Unesite upute:";
		getline(cin , upute);
		dodajRecept(naslov,upute);
		adminMeni();
		//Unos Artikala u vektor artikala
	}else if(adminOdabir==2){
		string imeArtikla;
		cout<<"Unesite ime artikla: ";
		cin.ignore();
		getline(cin , imeArtikla);
		int cijenaArtikla;
		cout<<"Unesite cijenu:";
		cin>>cijenaArtikla;
		vrstaPoslastice vrsta;
		cout<<"Unesite vrstu artikla: 1-Palacinka, 2-Kolac:"<<endl;
		int temp;
		cin>>temp;
		if(temp==1){
			vrsta=Palacinka;
		}else if(temp==2){
			vrsta=Kolac;	
		}else{
			cout<<"Unesena opcija nije postojeca!!!";
		}
		dodajArtikal(imeArtikla,cijenaArtikla,vrsta);
		//Povratak na glavni meni
	}else if(adminOdabir==3){
		cout<<"\t\t Odaberite opcije: " <<endl;
		cout<<"\t\t 1.Admin " <<endl;
		cout<<"\t\t 2.Kupac " <<endl;
		cout<<"\t\t 3.Izlaz " <<endl;
		return;
	}else if(adminOdabir==4){
		for(int i=0;i<kupci.size();i++){
					cout<<endl<<i+1<<". Kupac: "<<endl;
					cout<<"Ime Kupca: "<<kupci[i].ime<<endl;
					cout<<"Prezime Kupca: "<<kupci[i].prezime<<endl;
					cout<<"Spol Kupca: "<<kupci[i].spol<<endl;
					cout<<"Adresa Kupca: "<<kupci[i].adresa<<endl;
		}
		adminMeni();
	}
}


//korisnik Opcije
void korisnikMeni(){
	cout<<"			I---------------------------------I "<<endl;
	cout<<"			I                                 I "<<endl;
	cout<<"			I                                 I "<<endl;
	cout<<"			I     Welcome to our Cupcake!!!   I "<<endl;
	cout<<"			I                                 I "<<endl;
	cout<<"			I                                 I "<<endl;
	cout<<"			I                                 I "<<endl;
	cout<<"			I---------------------------------I "<<endl;
	
	int korisnikOdabir;
	cout<<"\t\t Odaberite opcije: " <<endl;
	cout<<"\t\t 1.Kupovina Artikla " <<endl;
	cout<<"\t\t 2.Pregled recepta " <<endl;
	cin>>korisnikOdabir;
	
	if(korisnikOdabir==1){
		//unos kupca za kupovinu
		unosKupca();
		if(poslastica.size()==0){
			cout<<"Nemamo artikala";
			int odabir;
		cout<<"\t\t Odaberite opcije: "<<endl;
		cout<<"\t\t 1. Admin "<<endl;
		cout<<"\t\t 2. Kupac "<<endl;
		cout<<"\t\t 3. Izlaz "<<endl;
		cin>> odabir;
		if(odabir>3 && odabir<1){
			system("CLS");
			cout<<"Unesena opcija nije postojeca!";
			cin>>odabir;
		}
		if(odabir==1){
			adminMeni();
			cin>>odabir;
		}
		if(odabir==2){
			korisnikMeni();
		}
		if(odabir==3){
			return;
		}
		return;
		}else{
			for(int i=0;i<poslastica.size();i++){
				cout<<endl<<i+1<<". Artikal: "<<endl;
				cout<<"Ime artikla: "<<poslastica[i].nazivPoslastice<<endl;
				cout<<"Cijena artikla: "<<poslastica[i].cijena<<endl;
				cout<<"Vrsta artikla: "<<poslastica[i].vrsta<<endl;
			}
			cout<<"Odabir zeljenog artikla: ";
			int odabirKupovine;
			cin>>odabirKupovine;
			if(odabirKupovine>poslastica.size()){
				cout<<"Nemamo taj artikal!";
			}else{
				cout<<"Artikal "<< poslastica[odabirKupovine-1].nazivPoslastice<< " ce biti dostavljen vama!";
			}
			int odabir;
		cout<<"\t\t Odaberite opcije: "<<endl;
		cout<<"\t\t 1. Admin "<<endl;
		cout<<"\t\t 2. Kupac "<<endl;
		cout<<"\t\t 3. Izlaz "<<endl;
		cin>>odabir;
		if(odabir>3 && odabir<1){
			system("cls");
			cout<<"Unesena opcija nije postojeca!";
			cin>>odabir;
		}
		if(odabir==1){
			adminMeni();
			cin>>odabir;
		}
		if(odabir==2){
			korisnikMeni();
		}
		if(odabir==3){
			return;
		}
			}
	}else if(korisnikOdabir==2){
		ifstream Recepti;
		string listaRecepta;
		Recepti.open("Recepti.txt");
		if(!Recepti){
			cout<<"Error: file could not be opened!"<<endl;
		}
		getline(Recepti,listaRecepta);
		while(!Recepti.eof()){
			cout<<listaRecepta<<endl;
			getline(Recepti, listaRecepta);
		}
		Recepti.close();
		int odabir;
		cout<<"\t\t Odaberite opcije: "<<endl;
		cout<<"\t\t 1. Admin "<<endl;
		cout<<"\t\t 2. Kupac "<<endl;
		cout<<"\t\t 3. Izlaz "<<endl;
		cin>>odabir;
		if(odabir>3 && odabir<1){
			system("cls");
			cout<<"Unesena opcija nije postojeca!";
			cin>>odabir;
		}
		if(odabir==1){
			adminMeni();
			cin>>odabir;
		}
		if(odabir==2){
			korisnikMeni();
		}
		if(odabir==3){
			return;
		}
	}
}


int main(){
	bool done= false;
	do{
		cout<<"			I---------------------------------I "<<endl;
		cout<<"			I                                 I "<<endl;
		cout<<"			I                                 I "<<endl;
		cout<<"			I     Welcome to our Cupcake!!!   I "<<endl;
		cout<<"			I                                 I "<<endl;
		cout<<"			I                                 I "<<endl;
		cout<<"			I                                 I "<<endl;
		cout<<"			I---------------------------------I "<<endl;
		
		int odabir;
		cout<<"\t\t Odaberite opcije: " <<endl;
		cout<<"\t\t 1.Admin " <<endl;
		cout<<"\t\t 2.Kupac " <<endl;
		cout<<"\t\t 3.Izlaz " <<endl;
		cin>>odabir;
		if(odabir>3 && odabir<1){
			system("CLS");
			cout<<"Unesena opcija nije postojeca!";
			cin>>odabir;
		}
		if(odabir==1){
			adminMeni();
			cin>>odabir;
		}
		if(odabir==2){
			korisnikMeni();
		}
		if(odabir==3){
			done=true;
		}
	}while(done=false);

	
   return 0;
}
