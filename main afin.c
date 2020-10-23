int main(){
    mpz_t a,b,m;
    char filename[100] = "cifrado.txt";
    char mensaje[100] = "Hola soy laturrA";

    mpz_init(a);
    mpz_init(b);
    mpz_init(m);

    mpz_set_str (a,"13",10);
    mpz_set_str (b,"15",10);
    mpz_set_str (m,"95",10);


    cifrarAfin(a,b,m,mensaje,filename);

    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(m);
    return 0;
}

/*Para descifrar*/
int main(){
    mpz_t a,b,m;
    char ciphertext[100] = "cifrado.txt";
    char mensaje[100] = "hola";

    mpz_init(a);
    mpz_init(b);
    mpz_init(m);

    mpz_set_str (a,"13",10);
    mpz_set_str (b,"15",10);
    mpz_set_str (m,"95",10);

    descifrarAfin(a,b,m,ciphertext);
    /*cifrarAfin(a,b,m,mensaje,filename);*/

    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(m);
    return 0;
}
