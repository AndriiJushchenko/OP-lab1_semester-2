//
// Created by Ющенко Андрей on 08.06.2023.
//

#include "HexaPent.h"

TPentagon findPentaWithLargest_P(TPentagon* pentagons, int numPentagons) {
    TPentagon maxPentagon = pentagons[0];
    for (int i = 1; i < numPentagons; i++) {
        if (pentagons[i].getPerimeter() > maxPentagon.getPerimeter()) {
            maxPentagon = pentagons[i];
        }
    }
    return maxPentagon;
}
THexagon findHexaWithSmallestArea(THexagon* hexagons, int numHexagons) {
    THexagon minHexagon = hexagons[0];
    for (int i = 1; i < numHexagons; i++) {
        if (hexagons[i].getArea() < minHexagon.getArea()) {
            minHexagon = hexagons[i];
        }
    }
    return minHexagon;
}

void mind() {

    int NumOfPentagons, NumOfHexagons;

    cout << "Enter the number of pentagons: ";
    cin >> NumOfPentagons;
    cout << "Enter the number of hexagons: ";
    cin >> NumOfHexagons;

    TPentagon* pentagons = new TPentagon[NumOfPentagons];

    for (int i = 0; i < NumOfPentagons; i++) {
        double x1, y1, x2, y2, x3, y3, x4, y4, x5, y5;
        cout << "Enter the coordinates x and y of the 1st point of pentagon #" << i + 1 << "(example: -2 3): ";
        cin >> x1 >> y1;
        cout << "Enter the coordinates x and y of the 2nd point of pentagon #" << i + 1 << "(example: 2 3): ";
        cin >> x2 >> y2;
        cout << "Enter the coordinates x and y of the 3rd point of pentagon #" << i + 1 << "(example: 4 -1): ";
        cin >> x3 >> y3;
        cout << "Enter the coordinates x and y of the 4th point of pentagon #" << i + 1 << "(example: 0 -3): ";
        cin >> x4 >> y4;
        cout << "Enter the coordinates x and y of the 5th point of pentagon #" << i + 1 << "(example: -4 -1): ";
        cin >> x5 >> y5;

        TPentagon pentagon(TPoint(x1, y1),
                           TPoint(x2, y2),
                           TPoint(x3, y3),
                           TPoint(x4, y4),
                           TPoint(x5, y5));
        pentagons[i] = pentagon;
        cout << "Pentagon #" << i + 1 << ": Perimeter = " << pentagon.getPerimeter() << ", Area = " << pentagon.getArea() << endl;
    }

    TPentagon maxPentagon = findPentaWithLargest_P(pentagons, NumOfPentagons);
    cout << "Pentagon with largest perimeter: " << endl;
    cout << "Perimeter: " << maxPentagon.getPerimeter() << endl;
    cout << "Area: " << maxPentagon.getArea() << endl << endl;


    THexagon* hexagons = new THexagon[NumOfHexagons];

    for (int i = 0; i < NumOfHexagons; i++) {
        double x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6;
        cout << "Enter the coordinates x and y of the 1st point of hexagon #" << i + 1 << "(example: 0 5): ";
        cin >> x1 >> y1;
        cout << "Enter the coordinates x and y of the 2nd point of hexagon #" << i + 1 << "(example: 4 2): ";
        cin >> x2 >> y2;
        cout << "Enter the coordinates x and y of the 3rd point of hexagon #" << i + 1 << "(example: 4 -3): ";
        cin >> x3 >> y3;
        cout << "Enter the coordinates x and y of the 4th point of hexagon #" << i + 1 << "(example: 0 -6): ";
        cin >> x4 >> y4;
        cout << "Enter the coordinates x and y of the 5th point of hexagon #" << i + 1 << "(example: -4 -3): ";
        cin >> x5 >> y5;
        cout << "Enter the coordinates x and y of the 6th point of hexagon #" << i + 1 << "(example: -4 2): ";
        cin >> x6 >> y6;

        THexagon hexagon(TPoint(x1, y1),
                         TPoint(x2, y2),
                         TPoint(x3, y3),
                         TPoint(x4, y4),
                         TPoint(x5, y5),
                         TPoint(x6, y6));
        hexagons[i] = hexagon;
        cout << "Hexagon #" << i + 1 << ": Perimeter = " << hexagon.getPerimeter() << ", Area = " << hexagon.getArea() << endl;
    }

    THexagon minHexagon = findHexaWithSmallestArea(hexagons, NumOfHexagons);
    cout << "Hexagon with smallest area: " << endl;
    cout << "Perimeter: " << minHexagon.getPerimeter() << endl;
    cout << "Area: " << minHexagon.getArea() << endl << endl;

    delete[] pentagons;
    delete[] hexagons;
}