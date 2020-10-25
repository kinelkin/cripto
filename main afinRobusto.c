int main(){
    mpz_t a,b,m;
    char fichero[100]="fichero.txt";
    char cifrado[100]="cifrado.txt";
    char plano[100]="plano.txt";
    int modulo;

    printf("Elija un módulo (Sugerencia: Cuanto mayor sea, más robusto será su cifrado):\n");
    scanf("%d", &modulo);
    mpz_init(a);
    mpz_init(b);
    mpz_init(m);

    mpz_set_str (a,"5",10);
    mpz_set_str (b,"15",10);
    mpz_set_str (b,"0",10);
    mpz_set_ui(m,modulo);


    cifrarAfin(a,b,m,fichero,cifrado);
    descifrarAfin(a,b,m,cifrado,plano);


    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(m);
    return 0;
}
