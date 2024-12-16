#include "semafor.h"

main(int argc, char **argv)
{
    key_t key = ftok(".", 'A'); // 12345
    int s_id;                   // semafor ID

    s_id = tworz(key, 1);

    cout << "\n\t[ proces " << getpid() << " ]";

    info(s_id);

    P(s_id, 0);
    cout << "\n\t[ sekcja krytyczna " << getpid() << " ]\n";
    info(s_id);
    sleep(5);
    V(s_id, 0);
    cout << "\n\t[ koniec sekcji krytycznej " << getpid() << " ]\n";
    info(s_id);

    return 0;
}
