int main(){
    mpz_t a,b,m;
    FILE* entrada;
    FILE* salida;


    mpz_init(a);
    mpz_init(b);
    mpz_init(m);

    mpz_set_str (a,"5",10);
    mpz_set_str (b,"15",10);
    mpz_set_str (m,"27",10);

    cifrarAfin(a,b,m,entrada,salida);
    descifrarAfin(a,b,m,entrada,salida);


    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(m);
    return 0;
}
