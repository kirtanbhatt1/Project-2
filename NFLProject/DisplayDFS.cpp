#include "DisplayDFS.h"

Database dfsDb;

DisplayDFS::DisplayDFS(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	QObject::connect(ui.importPushButton, &QPushButton::clicked, this, &DisplayDFS::showDFS);
}

DisplayDFS::~DisplayDFS()
{}
void DisplayDFS::clearLayout()
{
	for (int i = 0; i < allWidgets.size(); i++)
	{
		ui.verticalLayout_2->layout()->removeWidget(allWidgets.at(i));
		delete allWidgets[i];
	}
	for (int i = 0; i < allCountWidgets.size(); i++)
	{
		ui.verticalLayout_2->layout()->removeWidget(allCountWidgets.at(i));
		delete allCountWidgets[i];
	}

	allWidgets.clear();
	allCountWidgets.clear();
}
void DisplayDFS::showDFS()
{
	
	clearLayout();

	QVector<Team> allTeams = dfsDb.getTeams();

	Graph cities;

		
	for (int i = 0; i < allTeams.size(); i++)
	{
		cities.insertVertex(allTeams[i].getStadium().getStadiumName());
	}
			
	//prompting user for file input 
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open Text File"), "/home", tr("TXT Files (*.txt)"));

	QFile inputFile(fileName);
	QVector<QString> lines;

	if (inputFile.open(QIODevice::ReadOnly))
	{
		QTextStream in(&inputFile);

		while (!in.atEnd())
		{
			lines.push_back(in.readLine());
		}
		inputFile.close();
	}
	else
	{
		qCritical() << "Invalid File.";
	}

	if (lines.size() == 0)
	{
		qCritical() << "File is Empty!";
	}

	for (int i = 0; i < lines.length(); i++)
	{
		if (!lines[i].isEmpty())
		{
			QStringList list = lines[i].split("  ");

			QString startingStadium = list[0];
			QString endingStadium = list[1];
			int distance = list[2].toInt();

			cities.insertEdge(startingStadium, endingStadium, distance);
		}
		else
		{
			continue;
		}
	}
		

	cities.DFS(cities.getVertex("U.S. Bank Stadium"));
	
	for (int i = 0; i < cities.allEdgeDistances.size(); i++)
	{
		W_DFSList* dfsText = new W_DFSList(this);
	
		dfsText->setup(cities.allEdgeDistances[i].getStartingStadium(), cities.allEdgeDistances[i].getEndingStadium());
	
		ui.verticalLayout_2->addWidget(dfsText);
		allWidgets.push_back(dfsText);
	}
	W_TotalCount* totalDistanceWidget = new W_TotalCount(this);
	totalDistanceWidget->setup(cities.returnTotalDistance());
	totalDistanceWidget->setLabelText("Total Distance:");
	ui.verticalLayout_2->addWidget(totalDistanceWidget);
	allCountWidgets.push_back(totalDistanceWidget);
	
	cities.clear();
		
}
