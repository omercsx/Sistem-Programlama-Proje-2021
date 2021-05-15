#include <stdio.h>
#include <stdlib.h>
#include "../libfdr/jrb.h"
#include "../include/string_islem.h"
#include "../libfdr/fields.h"

#define E_PARAMETRESI "-e"
#define D_PARAMETRESI "-d"

int main(int argc, char **argv)
{

    IS kilit = new_inputstruct(".kilit"); // kilit dosyasi okunur
    if (kilit == NULL)                    // kilit dosyasi yoksa hata verir ve cikiş yapar
    {
        fprintf(stderr, ".kilit dosyasi bulunamadi");
        exit(1);
    }

    JRB kilitAgac;          // burada kilit dosyasının verilerini yazacağımız red-black ağacını tanımladık
    kilitAgac = make_jrb(); // boş ağaç oluşturduk ve kilitAgac'ın içine atadık

    if (strcmp(argv[1], D_PARAMETRESI) == 0)
    { // eğer -d paremetresi verdiysek burası çalışıcak

        IS giris_Dosyasi = new_inputstruct(argv[2]); // giris dosyasinı okuyoruz
        if (giris_Dosyasi == NULL)
        {
            fprintf(stderr, "giris dosyasi okunamadi");
            exit(1);
        }

        FILE *Cikis_dosyasi; //çıkış dosyasini tanımladık

        if (argv[3] == NULL)
        {
            if ((Cikis_dosyasi = fopen("decripted", "w")) == NULL)
            {
                printf("yazilacak dosya acilamadi");
            }
        }
        else
        {
            if ((Cikis_dosyasi = fopen(argv[3], "w")) == NULL)
            {
                printf("yazilacak dosya acilamadi");
            }
        }

        JRB Aranan_agac_dugumu;
        Hash *arahash;

        Hash *h;
        int i, t, l;
        h = (Hash *)malloc(sizeof(Hash));

        while (get_line(kilit) >= 0)
        { // burası kilit dosyasini ağaca atadığımız yer

            for (i = 1; i < kilit->NF; i++)
            {

                l = i;
                h = yazdir(kilit->fields[i], kilit->fields[--l]);               //key value
                (void)jrb_insert_str(kilitAgac, h->key, new_jval_s((void *)h)); // Hash yapısını ağacın içine ekliyoruz
            }
        }

        while (get_line(giris_Dosyasi) >= 0) // giriş dosyasini okuyoruz ve ağacın içinde arama yapıyoruz
        {
            for (int j = 0; j < giris_Dosyasi->NF; j++)
            {
                Aranan_agac_dugumu = jrb_find_str(kilitAgac, giris_Dosyasi->fields[j]);

                if (Aranan_agac_dugumu == NULL)
                {
                    printf("%s ", giris_Dosyasi->fields[j]);
                    fprintf(Cikis_dosyasi, "%s ", giris_Dosyasi->fields[j]);
                }
                else
                {
                    arahash = (Hash *)Aranan_agac_dugumu->val.v;
                    printf("%s ", arahash->value);
                    fprintf(Cikis_dosyasi, "%s ", arahash->value);
                }
            }
        }

        fclose(Cikis_dosyasi);

        jettison_inputstruct(kilit); // okuduğumuz dosyaları bellekten boşaltıyoruz ve çıkış yapıyoruz
        jettison_inputstruct(giris_Dosyasi);

        return 0;
    }
    else if (strcmp(argv[1], E_PARAMETRESI) == 0)
    {

        IS giris_Dosyasi = new_inputstruct(argv[2]);
        if (giris_Dosyasi == NULL)
        {
            fprintf(stderr, "giris dosyasi okunmasi basarisiz");
            exit(1);
        }

        FILE *Cikis_dosyasi;

        if (argv[3] == NULL)
        {
            if ((Cikis_dosyasi = fopen("encripted", "w")) == NULL)
            {
                printf("yazilacak dosya acilmasi basarisiz");
            }
        }
        else
        {
            if ((Cikis_dosyasi = fopen(argv[3], "w")) == NULL)
            {
                printf("yazilacak dosya acilmasi basarisiz");
            }
        }

        JRB Aranan_agac_dugumu;
        Hash *arahash;

        Hash *h;
        int i, t, l;
        h = (Hash *)malloc(sizeof(Hash));

        while (get_line(kilit) >= 0)
        {
            for (i = 1; i < kilit->NF; i++)
            {
                l = i;
                h = yazdir(kilit->fields[i], kilit->fields[--l]);
                (void)jrb_insert_str(kilitAgac, h->value, new_jval_s((void *)h));
            }
        }

        while (get_line(giris_Dosyasi) >= 0)
        {
            for (int j = 0; j < giris_Dosyasi->NF; j++)
            {
                Aranan_agac_dugumu = jrb_find_str(kilitAgac, giris_Dosyasi->fields[j]);
                if (Aranan_agac_dugumu == NULL)
                {
                    printf("%s ", giris_Dosyasi->fields[j]);
                    fprintf(Cikis_dosyasi, "%s ", giris_Dosyasi->fields[j]);
                }
                else
                {
                    arahash = (Hash *)Aranan_agac_dugumu->val.v;
                    printf("%s ", arahash->key);
                    fprintf(Cikis_dosyasi, "%s ", arahash->key);
                }
            }
        }

        fclose(Cikis_dosyasi);

        jettison_inputstruct(kilit);
        jettison_inputstruct(giris_Dosyasi);

        return 0;
    }
    else
    {
        fprintf(stderr, "yanlis parametre girdiniz.\n");
        exit(1);
    }

    return 0;
}