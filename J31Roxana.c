#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <dos.h>


typedef struct {
   int  valor;
   char mazo ;
} carta;


typedef struct {
   int score;
   int turn;
   char name[12];
} players;



//Variable para jugador y banquero.
players user;
players bank;

//Variable para las cartas
carta todasCartas[48];
char cartasFinales1[10][4];
char cartasFinales2[10][4];
//posicion en cartas finales
int p1, p2 = 0;


//funcion para asignasr valores a las cartas. Parametros: inicio, limite, nombre de mazo
carta asignarValores(int ini, int limit, carta name[]){
  	for(ini; ini < limit; ini++){
	  name[ini].valor = ini+1;
}
}


int main (void) {
	
	//*Crear mazos de cartas*
	
	carta mazo1[12];
	carta mazo2[12];
	carta mazo3[12];
	carta mazo4[12];

	
	//*Asignar valores para cartas
	
	asignarValores(1,13, mazo1);
    asignarValores(1,13, mazo2);
    asignarValores(1,13, mazo3);
    asignarValores(1,13, mazo4);
		
     //Inicio del juego. Asignacion de nombres y turnos
		puts("Bienvenido a Juego 31\n");
	printf("Cual es tu nombre? ");
   	char nombre[10];
   	scanf("%s", &nombre);
	int turno = 1;
	printf("\n %s tienes el turno %i \n", nombre, turno);
	strcpy(user.name, nombre);
    strcpy(bank.name, "banquero");
    user.turn = 1;
    bank.turn = 2;
    
	
	puts("----------------------------------------------------------------------------");

//funcion que une todos los mazos en uno solo. Parametros: inicio, limite, nombre mazo1, nombre mazo2, char simboloDeMazo
carta unirMazos(int ini, int limit, carta name1[], carta name2[], char sm){
  	 for(ini; ini<limit; ini++){
	 name1[ini] = name2[ini];
	 name1[ini].mazo = sm;
    }
  }

    unirMazos(1, 13, todasCartas, mazo1, 'T');
    unirMazos(13, 25, todasCartas, mazo2, 'E');
    unirMazos(25, 37, todasCartas, mazo3, 'D');
    unirMazos(37, 49, todasCartas, mazo4, 'C');
    
   //Repartir primeras cartas
	printf("Tus cartas son... \n");
  int sc = repartirCartas(user,0,3,0, 1);
  int sb =  repartirCartas(bank,1,3,0, 2);
  
  //Repartir cartas adicionales
   continuar(user, sc, user.turn);
   if(sb < 27){
   continuar(bank, sb, 2);
   }
  
  //Comparar los puntajes y declarar ganador.
 compararPuntaje(user.score, bank.score );
 //Reiniciar juego
	reiniciar();
	return 0;
}
 
 
 
 int repartirCartas(players player, int in, int cartasNum, int total, int turn){
 	
   time_t t;
   int i, ii, pos;
   int size = 48;
   srand((unsigned)time(&t)+in);
   player.score = total;
   
   for(i=1;i<(cartasNum+1);i++){  
         pos = rand()%size;
   	    carta cartasRepartidas = todasCartas[pos]; 
   	    if(cartasRepartidas.valor == todasCartas[0].valor){
   	    	cartasRepartidas = todasCartas[1];}
   	     //Saca la carta repartida
	   for(ii=pos-1; ii<size-1; ii++) { todasCartas[ii] = todasCartas[ii + 1];}
             size--;	
			   	 
        char result = (char) cartasRepartidas.valor +'0';
   	
   	    
		   switch (cartasRepartidas.valor) {
            case 10:
            cartasRepartidas.valor = 10;
            unirCadena(player, 'J', cartasRepartidas.mazo);
            break;

            case 11:
            cartasRepartidas.valor = 10;
     	    unirCadena(player, 'Q', cartasRepartidas.mazo);
            break;

            case 12:
            cartasRepartidas.valor = 10;
     	    unirCadena(player,'K', cartasRepartidas.mazo); 
            break;

            case 13:
            cartasRepartidas.valor = 11;	
            unirCadena(player, 'A', cartasRepartidas.mazo); 
            break;
			         
			default:   unirCadena(player, result, cartasRepartidas.mazo); 
   	       }
   	      
   	
   	    //Preguntar que valor se asignara a As
        if(cartasRepartidas.valor == 11) {
   	       if(player.turn == 1){
   	       printf("Que valor le asignaras a As. Escribe 1 o 11 ");
   	       int num;
   	       scanf("%d", &num);
   	       
   	     	switch (num) {
                case 1:
     	        cartasRepartidas.valor = 1;
                break;

                case 11:
                cartasRepartidas.valor = 11;
                break;
				} 
			}
		}
	
		
		//actualiza posicion cartas finales
		if(player.turn == 1){
		  p1++;;
		} else p2++;
		//Contar puntaje
	   player.score += cartasRepartidas.valor;
	   
	  
	     
 }
	
   
  
   //Mostrar puntaje
   if(player.turn == 1){
   	user.score = player.score;
 	printf("\nTu puntaje es %i \n", player.score);
 	
 	if(user.score > 31){
    printf("\n Has perdido la partida\n");
    reiniciar();
   }
    if(user.score == 31){
    printf("\n Has ganado la partida\n");
    reiniciar();
   }
   } else {
   	bank.score = player.score;
   }
   
   
   
 	return player.score;
}

void unirCadena(players user, char valor, char mazo){
   
	char str[2];
	str[0] = valor;
	str[1] = '\0';
    strncat(str, &mazo, 1); 
    if(user.turn == 1){
    printf("%s \n", str);
	strcpy(cartasFinales1[p1], str);
	 } else {
	 strcpy(cartasFinales2[p2], str);
	 
	 }  
}

int continuar(players player, int total, int turn){
	
	//Preguntar si desea continuar
   char qc;
   int st;
   if(player.turn == 1){
   printf("\nSi deseas quedarte digita 'q', para continuar digita 'c' "); scanf(" %c", &qc);
   
	switch (qc){

		case 'c' :
	    st = repartirCartas(player, 2, 1, total, turn);
		return continuar(player,st,turn);
		break;     
        
        case 'q' : break;
        
        default: break;
	}
} else repartirCartas(bank, 3, 1, total, 2);
	return 0;
}

int compararPuntaje(score1, score2){
	int i;
	printf("\nScore jugador %i  ", score1 );
	printf("Score banquero %i\n", score2 );
   
   if (score1 > score2){
   printf("\nHas ganado la partida\n");
   } else if (score1 == score2){
   	 printf("\nHa habido un empate\n");
   } else printf("\nHas perdido la partida\n");
   
   printf("\nCartas de %s : ", user.name);
    for(i = 0; i < (p1+1); i++)
    {
      printf(" %s ", cartasFinales1[i]);
    }
    
    printf("\nCartas de %s : ", bank.name);
    for(i = 0; i < (p2+1); i++)
    {
      printf(" %s ", cartasFinales2[i]);
    }
   
    //para reiniciar cartas finales
     p1 = 0; p2 = 0;
    for (i=0; i<(p1+1); i++){
      cartasFinales1[i][0] = 0;}
    for (i=0; i<(p2+1); i++){
      cartasFinales2[i][0] = 0;}
      
   return 0 ;
}

void reiniciar(){
	char confirmar[3];
	puts("                          ");
 printf("\nQuieres jugar otra vez? Si o No\n");
 scanf("%s", &confirmar);
 while (strcmp(confirmar, "si") == 0){
 	system("pause");
	system("cls");
    main();
} exit(0);
}



