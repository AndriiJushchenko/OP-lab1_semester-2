#include "streamwork.h"
#include "pointerwork.h"



int main(int argc, char *argv[]) {
    if (argc == 3 and strcmp(argv[2], "filestream")==0) {
        cout << "Stream mode is activated\n";
        filestream();
    } else if (argc == 3 and strcmp(argv[2], "filepoint")==0) {
        cout << "Pointer mode is activated\n";
        filepointer();
    } else {
        cout << "No such mode exists";
    }
    return 0;
}