# Sistem-Programlama-Proje-2021
Sakarya Üniversitesi Bilgisayar Mühendisliği Sistem Programlama dersi için proje ödevi Reposu

# Grup Üyeleri ve Görevleri

1 - Ömer Çağrı Şayir (G171210028): Proje sorumlusu

2 - Arif Damar (G171210009): Json formatında kilit dosyasının okunması

3 - Emin Utku Mert (G171210051): Encode ve decode işlemlerinin yapılması

4 - Ecem Amanvermez (G181210022): Deployment Sorumlusu

projede libfdr kütüphanesiyle şifreleme uygulaması yaptık. proje önce .kilit dosyası okunup okunan değerler red-black ağacına ekleniyor. burası okuma kısmı 

```c
  IS kilit = new_inputstruct(".kilit");// kilit dosyasi okunur 
    if (kilit == NULL)// kilit dosyasi yoksa hata verir ve cikiş yapar
    {
        fprintf(stderr, ".kilit dosyasi bulunamadi");
        exit(1);
    }
```
burdada okuduğumuz değerleri agacın içine yerleştiriyoruz ağaca eklerken key değerini girilen paremetreye göre değiştiriyoruz eğer normal kelime arıyorsak ağacın içinde ağacın key yerine kelimeleri yazıyoruz eğer şifrelenmiş olarak arıyorsak o zaman ağacın key yerine şifrelenmiş olrak yüklüyoruz. bu bize ağacın içinde arama yapmamızı sağlıyor
```c
while(get_line(kilit) >= 0){ // burda kilit dosyasini ağaca atadığımız yer 
    for( i = 1; i < kilit->NF; i++)
    {
        l = i;
        h = yazdir(kilit->fields[i] ,kilit->fields[--l]);//key value
        (void) jrb_insert_str(kilitAgac, h->key, new_jval_s((void *) h));// Hash yapısını ağacın içine ekliyoruz
    }
}
```

ağacın valu değerini Hash isimli özel bir veri yapası oluşturarak ekledik bu bize ağacın içinde arama yaptığımızda key value olrak cekmemizi sağlıyor.

```c
typedef struct Hash{
    char *key;
    char *value;
}
```

girilen parametreye göre ağacın içnide arama yapıyoruz ve elde ettiğimz değeri cıkış dosyasına yazıyoruz. 
```c
    while (get_line(giris_Dosyasi) >= 0)
        {
            for (int j = 0; j < giris_Dosyasi->NF; j++) 
            {
                Aranan_agac_dugumu = jrb_find_str(kilitAgac,giris_Dosyasi->fields[j]);
                if(Aranan_agac_dugumu== NULL){
                    printf("%s ",giris_Dosyasi->fields[j]);
                    fprintf(Cikis_dosyasi,"%s ",giris_Dosyasi->fields[j]);
                }else{
                    arahash = (Hash *) Aranan_agac_dugumu->val.v;
                    printf("%s ", arahash->key);
                    fprintf(Cikis_dosyasi, "%s ", arahash->key);
                }
            } 
        }
```

en son olarak bellekte kullanmadığımız yerleri silip programdan çıkıyoruz
```c
    jettison_inputstruct(kilit);
    jettison_inputstruct(giris_Dosyasi);
```
