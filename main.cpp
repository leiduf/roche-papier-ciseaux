#include <iostream>
#include <string>
#include <clocale>
#include <cstdlib>
#include <conio.h>

#include "Windows.h"

using namespace std;

enum class Mains
{
	Inconnu,
	Roche,
	Papier,
	Ciseaux
};

enum class Resultat
{
	Inconnu,
	Victoire,
	Defaite,
	Nulle,
};

int Random()
{
	return (rand() % 3 + 1);
}

Mains faireChoix()
{
	int ex{ _getch() };
	switch (ex)
	{
	case 'c':
	case 'C':
		cout << endl << "Vous avez choisi \x1B[1mciseaux\x1B[0m." << endl;
		return Mains::Ciseaux;
	case 'p':
	case 'P':
		cout << endl << "Vous avez choisi \x1B[1mpapier\x1B[0m." << endl;
		return Mains::Papier;
	case 'r':
	case 'R':
		cout << endl << "Vous avez choisi \x1B[1mroche\x1B[0m." << endl;
		return Mains::Roche;
	default:
		return Mains::Inconnu;
	}
}

Resultat determinerResultat(Mains mainJoueur, Mains mainOrdi)
{
	if (mainJoueur == mainOrdi)				return Resultat::Nulle;

	//Est roche
	if (mainJoueur == Mains::Roche)
	{
		if (mainOrdi == Mains::Papier)		return Resultat::Defaite;
		if (mainOrdi == Mains::Ciseaux)		return Resultat::Victoire;
	}
	//Est papier
	if (mainJoueur == Mains::Papier)
	{
		if (mainOrdi == Mains::Roche)		return Resultat::Victoire;
		if (mainOrdi == Mains::Ciseaux)		return Resultat::Defaite;
	}
	//Est ciseaux
	if (mainJoueur == Mains::Ciseaux)
	{
		if (mainOrdi == Mains::Roche)		return Resultat::Defaite;
		if (mainOrdi == Mains::Papier)		return Resultat::Victoire;
	}
	return Resultat::Inconnu;
}

void afficherMainJoue(Mains main, string qui)
{
	switch (main)
	{
	case Mains::Roche:
		cout << endl << qui << " joue \x1b[1mroche\x1b[0m";
		Sleep(500);
		cout << ".";
		Sleep(500);
		cout << ".";
		Sleep(500);
		cout << "." << endl;
		break;
	case Mains::Papier:
		cout << endl << qui << " joue \x1b[1mpapier\x1b[0m";
		Sleep(500);
		cout << ".";
		Sleep(500);
		cout << ".";
		Sleep(500);
		cout << "." << endl;
		break;
	case Mains::Ciseaux:
		cout << endl << qui << " joue \x1b[1mciseaux\x1b[0m";
		Sleep(500);
		cout << ".";
		Sleep(500);
		cout << ".";
		Sleep(500);
		cout << "." << endl;
		break;
	}
}

void afficherResultat(Resultat resultatPartie, Mains mainJoueur, Mains mainOrdi)
{
	cout << "----------------------------------------" << endl;
	afficherMainJoue(mainJoueur, "L'utilisateur");
	afficherMainJoue(mainOrdi, "L'ordi");

	switch (resultatPartie)
	{
	case Resultat::Victoire:
		cout << endl << "\x1b[1mVous avez gagné !" << endl;
		break;
	case Resultat::Defaite:
		cout << endl << "\x1b[1mVous avez perdu !" << endl;
		break;
	case Resultat::Nulle:
		cout << endl << "\x1b[1mVous avez fait égalité !" << endl;
		break;
	default:
		cout << "Erreur";
		break;
	}

	cout << endl << "\x1b[0m----------------------------------------" << endl << endl;
}

//Prendre en compte le pluriel dans le sommaire
void afficherSommaire(string categorie, int nombre)
{
	cout << "Partie";
	if (nombre > 1)
	{
		cout << "s";
	}
	cout << " " + categorie;
	if (nombre > 1)
	{
		cout << "s";
	}
	cout << ": " << nombre << endl;
}

void faireSommaire(Resultat resultatPartie, int& victoire, int& defaite, int& nulle)
{
	switch (resultatPartie)
	{
	case Resultat::Victoire:
		victoire++;
		break;
	case Resultat::Defaite:
		defaite++;
		break;
	case Resultat::Nulle:
		nulle++;
		break;
	}

	cout << endl << "--------------- Sommaire ---------------" << endl
		<< endl;
	afficherSommaire("gagnée", victoire);
	afficherSommaire("perdue", defaite);
	afficherSommaire("nulle", nulle);
	cout << endl
		<< "----------------------------------------" << endl;
}

void clear_screen()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void ConfigurerConsole()
{
	setlocale(LC_ALL, "");
	srand((unsigned int)time(NULL));

#ifdef _WIN32
	system("cls");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD a;
	a.X = 90;
	a.Y = 300;

	SMALL_RECT rect;
	rect.Top = 0;
	rect.Left = 0;
	rect.Bottom = 12;
	rect.Right = 40;


	SetConsoleScreenBufferSize(handle, a);
	SetConsoleWindowInfo(handle, 1, &rect);
	SetConsoleTitle(L"Roche, Papier, Ciseaux");
#else
	system("clear");
#endif
}

void pause()
{
#ifdef _WIN32
	system("pause");
#else
	cout << "Appuyez sur une touche pour continuer..." << endl;
	_getch();
#endif
}

bool faireChoixYN(const string& instruction)
{
	cout << endl << instruction << " (Y/N)" << endl;

	while (true)
	{
		char c = _getch();
		switch (c)
		{
		case 'N':
		case 'n':
			return false;
		case 'Y':
		case 'y':
			return true;
		default:
			break;
		}
	}
}

int main(void)
{
	ConfigurerConsole();

	int victoire{ 0 };
	int defaite{ 0 };
	int nulle{ 0 };
	Mains mainJoueur{};
	bool veutRejouer{ true };
	do
	{
		// 1er écran, menu, choix
		clear_screen();
		cout << "-------- Roche, Papier, Ciseaux --------" << endl
			<< "Choisir: " << endl
			<< endl
			<< "\x1b[1mR\x1b[0moche" << endl
			<< "\x1b[1mP\x1b[0mapier" << endl
			<< "\x1b[1mC\x1b[0miseaux" << endl
			<< endl
			<< "----------------------------------------" << endl;
		mainJoueur = faireChoix();

		if (mainJoueur != Mains::Inconnu)
		{
			bool choixEstConfirme{ faireChoixYN("Confirmez votre choix") };

			if (choixEstConfirme)
			{
				// 2e écran, déroulement, résultat

				clear_screen();
				Mains mainOrdi{ Mains(Random()) };
				Resultat resultatPartie{ determinerResultat(mainJoueur, mainOrdi) };
				if (resultatPartie == Resultat::Inconnu)
				{
					return -1;
				}
				afficherResultat(resultatPartie, mainJoueur, mainOrdi);
				pause();

				// 3e écran, sommaire, new game
				clear_screen();
				faireSommaire(resultatPartie, victoire, defaite, nulle);

				veutRejouer = faireChoixYN("Faire une nouvelle partie");
			}
		}
	} while (veutRejouer);

	return 0;
}