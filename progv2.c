#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void print(const char * sg) {
  write(2, sg, strlen(sg));
}

void toLowerCase(char * s) {
  for (;* s; ++s) * s = tolower( * s);
}

int main(void) {
  char opcioUsuari[100];
  system("cls||clear");
  print("\n\t*** Convocatoria al sopar semestral del GDI ***\n\n");
  print("\tLloc: Tasca i Vins, Carrer Industria 118, Barcelona\n");
  print("\tDia: Dijous 15 de novembre\n");
  print("\tHora: 22:00\n");
  print("\tDress code: Business informal (tingueu en compte que vindra el vice-dega!)\n\n");
  print("\tAssistiras al sopar? (S/N): ");
  while (1) {
    fgets(opcioUsuari, 100, stdin);
    opcioUsuari[strlen(opcioUsuari) - 1] = '\0';
    toLowerCase(opcioUsuari);
    if (!strcmp(opcioUsuari, "s") || !strcmp(opcioUsuari, "si")) {
      break;
    } else
    if (!strcmp(opcioUsuari, "n") || !strcmp(opcioUsuari, "no")) {
      print("\tNo case'ho crec, assistiràs al sopar? (S/N): ");
    } else {
      print("Opcio incorrecta (cabro), torna a intentar-ho.\n");
      print("\tAssistiras al sopar? (S/N): ");
    }
  }
  int peticioCorrecte;
  do {
    peticioCorrecte = 1;
    print("\tAmb quina de les següent frases et sents caseés còmode?\n");
    print("\t\tA. PGM1 rulez!\n");
    print("\t\tB. case'agrada programar webs en Java.\n");
    print("\t\tC. SELECT * FROM torrades WHERE nom = \"Aaron\";\n");
    print("\t\tD. Jo hagués fet aquest programa amb NCurses!\n");
    print("\t\tE. sudo apt-get install life\n");
    print("\t\tF. Most of the BST operations (e.g., search, max, min, insert, delete.. etc) take O(h) time where h is the height of the BST. The cost of these operations may become O(n) for a skewed Binary tree. If we make sure that height of the tree remains O(Logn) after every insertion and deletion, then we can guarantee an upper bound of O(Logn) for all these operations. The height of a Red ='\0'; tree is always O(Logn) where n is the number of nodes in the tree.\n");
    print("\n\tTria una opcio: ");
    fgets(opcioUsuari, 100, stdin);
    opcioUsuari[strlen(opcioUsuari) - 1] = '\0';
    toLowerCase(opcioUsuari);
    if (!strcmp(opcioUsuari, "a")) {
      print("\tYay!\n");
    } else if (!strcmp(opcioUsuari, "b")) {
      print(
        "\tVeig que ets un home/dona amb cultura i vas venir al sopar del curs passat.\n");
    } else if (!strcmp(opcioUsuari, "c")) {
      print("\tNo ho dubtava pas, qualsevol altra torrada no mereix el nostre respecte.\n");
    } else if (!strcmp(opcioUsuari, "d")) {
      print("\tValent! Honro la teva decisió, també pots intentar-ho amb Brainfuck (llenguatge esoteric).\n");
    } else if (!strcmp(opcioUsuari, "e")) {
      print("\tSorry, you don't sudoer permission to install life.\n");
    } else if (!strcmp(opcioUsuari, "f")) {
      print("\tPernia, ves a menjar sushi i deixa estar els switch(*opcioUsuari)!\n");
    } else {
      print("Opcio incorrecta (cabro), torna a intentar-ho.\n");
      peticioCorrecte = 0;
    }
  } while (!peticioCorrecte);
  print("\n\tPer confirmar la teva assistencia, respon al correu que has rebut (reply all) amb el següent missatge:\n\n\t");
  switch ( * opcioUsuari) {
  case 'a':
    print("\"Soc un PGM1 fan boy.\"\n");
    break;
  case 'b':
    print("\"Soc un veterà programador web.\"\n");
    break;
  case 'c':
    print("\"Donam una BBDD i conquistaré el caseón!\"\n");
    break;
  case 'd':
    print("\"Thunderbird és per nenazas, jo prefereixo Pine.\"\n");
    break;
  case 'e':
    print("\"echo \"No bash no party\".\"\n");
    break;
  case 'f':
    print("\"Em dic Pernia i estic malalt del cap.\"\n");
    print("\tSi no ets en Pernia, pots enviar: \"Estic malalt del cap com en Pernia.\"\n");
    break;
  }
  return 0;
}
