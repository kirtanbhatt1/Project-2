#include "DisplayMST.h"


DisplayMST::DisplayMST(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

DisplayMST::~DisplayMST()
{}
void DisplayMST::clearLayout()
{
	for (int i = 0; i < allWidgets.size(); i++)
	{
		ui.verticalLayout_2->layout()->removeWidget(allWidgets.at(i));
		delete allWidgets[i];
	}
	allWidgets.clear();

	for (int i = 0; i < countWidgets.size(); i++)
	{
		ui.verticalLayout_2->layout()->removeWidget(countWidgets.at(i));
		delete countWidgets[i];
	}
	countWidgets.clear();
}
void DisplayMST::showMST()
{
	clearLayout();

	QVector<QVector<int>> edges = { {0, 1, 870 }, {0, 2, 650}, {0, 3, 1115}, {0, 4, 580}, {0, 5, 372}, {0, 24, 372},	//Arizona - 0
									{18, 1, 740}, {18, 6, 225}, {18, 7, 600}, {18, 8, 425}, {18, 9, 375},				//Atlanta - 19
									{29, 10, 90}, {29, 11, 80},															// Baltimore - 29
									{30, 12, 210}, {30, 13, 429}, {30, 14, 225},{30, 15, 430}, {30, 16, 430},			//Buffalo - 30 
									{6, 17, 342}, {6, 10, 340}, {6, 18, 225},{6, 14, 365},								//Carolina - 6
									{31, 19, 415}, {31, 15, 80}, {31, 20, 50},											//Chicago - 31
									{9, 21, 225},{9, 18, 375}, {9, 14, 260}, {9, 20, 250}, {9, 22, 240},				//Cincinnai - 9 
									{21,12,90}, {21,14,115}, {21, 9, 225},												//Cleveland 21
									{1, 19, 460}, {1, 18, 740}, {1, 3, 230}, {1, 4, 650}, {1, 0, 870},					//Dalllas - 1 
									{4, 1, 650}, {4, 19, 560}, {4, 2, 930}, {4, 5, 1015}, {4, 24, 1015}, {4, 0, 580},	//Denver - 4 
									{12, 21, 90}, {12, 20, 240}, {12, 30, 210},											// Detroit 12
									{15, 30, 430}, {15, 31, 80}, {15, 27, 300},											// Green Bay 15
									{3, 1, 230}, {3, 7, 965}, {3, 8, 320}, {3, 22, 670}, {3, 0, 1115},					//Houston 3 
									{20, 12, 240}, {20, 9, 250}, {20, 31, 50},											//Indianapolis 20
									{17, 6, 342}, {17, 23, 170}, {17, 7, 315},											//Jacksonville 17
									{19, 1, 460}, {19, 22, 470}, {19, 31, 415}, {19, 4, 560},							//Kansas City 19
									{28, 16, 680}, {28, 2, 25}, {28, 5, 270}, {28, 24, 270},							//Las Vegas 28
									{24, 4, 1015}, {24,28,270}, {24,2,200}, {24, 0, 372}, {24, 27, 1500},				//Los Angeles Chargers - 24
									{5,4, 1015}, {5,0,372}, {5, 2, 200}, {5, 28, 270}, {5, 27, 1500},					//Los Angeles Rams - 5
									{7, 17, 315}, {7, 18, 600}, {7, 13, 1255}, {7, 3, 965}, {7, 23, 210},				//7 - Miami
									{27, 16, 1390}, {27, 15, 300}, {27, 22, 700}, {27, 5, 1500}, {27, 24, 1500},		//Minnesota 27 
									{13, 7, 1255}, {13, 30, 429}, {13, 25, 195}, {13, 26, 195},							//New England - 13
									{8, 3, 320}, {8, 18, 425}, {8, 23, 480},											//New Orlenas - 8
									{25, 13, 195}, {25, 11, 50},														// New York Giants - 25
									{26, 13, 195}, {26, 11, 50},														// New York Jets - 26
									{11, 14, 315}, {11, 29, 80}, {11, 25, 50},{11, 26, 50},								//Philadelphia - 11 
									{14, 6, 365}, {14, 21, 115}, {14, 11, 315}, {14, 9, 260}, {14, 30, 225},			//Pittsburgh 14
									{2, 28, 25}, {2, 4, 930}, {2, 5, 200}, {2, 24, 200}, {2, 0, 650},					// SFO - 2
									{16, 28, 680}, {16, 30, 2070}, {16, 27, 1390},										//Seattle - 16
									{23, 17, 170}, {23, 7, 210}, {23, 8, 480},											// Tampa - 23
									{22, 19, 470}, {22, 3, 670}, {22,9,240}, {22,27,700},								//Tenn 22
									{10, 6, 340}, {10, 29, 90} };														// Wash 10
	


	QVector<QString> vertices = { "Arizona Cardinals", "Dallas Cowboys", "San Francisco 49ers", "Houston Texans",
									"Denver Broncos", "Los Angeles Rams", "Carolina Panthers", "Miami Dolphins",
									"New Orleans Saints", "Cincinnati Bengals", "Washington Redskins", "Philadelphia Eagles",
									"Detroit Lions", "New England Patriots", "Pittsburgh Steelers", "Green Bay Packers",
									"Seattle Seahawks", "Jacksonville Jaguars", "Atlanta Falcons", "Kansas City Chiefs",
									"Indianapolis Colts", "Cleveland Browns", "Tennessee Titans", "Tampa Bay Buccaneers",
									"Los Angeles Chargers", "New York Giants", "New York Jets", "Minnesota Vikings",
									"Las Vegas Raiders", "Baltimore Ravens", "Buffalo Bills", "Chicago Bears"} ; 


	Prim_jarnik prim_mst(edges, vertices);
	int total = prim_mst.run();

	for (int i = 0; i < prim_mst.startNames.length(); i++)
	{
		W_DFSList* mstEdge = new W_DFSList(this);
		mstEdge->setup(prim_mst.startNames[i], prim_mst.endNames[i]);
		
		ui.verticalLayout_2->addWidget(mstEdge);
		allWidgets.push_back(mstEdge);
	}

	W_TotalCount* totalCount = new W_TotalCount(this);
	totalCount->setup(total);
	totalCount->setLabelText("Total Mileage:");
	ui.verticalLayout_2->addWidget(totalCount);
	countWidgets.push_back(totalCount);

}