int main(){
    mpz_t a,b,m;
    FILE* ciphertext;

    char filename[100] = "cifrado.txt";
    char filename2[100] = "plano.txt";

    char mensaje[100] = "Probando que funcione el cifrado afín";
    ciphertext = fopen("salida.txt", "r");
    mpz_init(a);
    mpz_init(b);
    mpz_init(m);

    mpz_set_str (a,"19",10);
    mpz_set_str (b,"15",10);
    mpz_set_str (m,"253",10);

    cifrarAfin(a,b,m,mensaje,filename);
    descifrarAfin(a,b,m,ciphertext);

    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(m);
    fclose(ciphertext);
}
