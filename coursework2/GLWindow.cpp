#include "GLWindow.h"

static const int INITIAL_OBJECT_INDEX = 1;
static const int INITIAL_COLOUR_INDEX = 0;

GLWindow::GLWindow(QWidget* parent, Drawable* drawableObject)
	: QWidget(parent), drawable(drawableObject)
{
	// Define list of drawable objects
	QStringList objectNameList;
	objectNameList << "Tetrahedron" << "Cube" << "Octahedron" << "Dodecahedron" << "Icosahedron";
	QStringList colourNameList;
	colourNameList << "Same" << "Alternate" << "Interpolate";

	setWindowTitle("COMP3811 Computer Graphics - Coursework One - Donald Whyte");
	windowLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

	// Menu bar
	menuBar = new QMenuBar(this);
	fileMenu = menuBar->addMenu("&File");
	actionQuit = new QAction("&Quit", this);
	fileMenu->addAction(actionQuit);

	// Row one, which contains OpenGL widget and verticval slider
	rowOneLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	windowLayout->addLayout(rowOneLayout);

	canvasWidget = new GLCanvasWidget(this, drawableObject);
	rowOneLayout->addWidget(canvasWidget);

	rowTwoLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	windowLayout->addLayout(rowTwoLayout);
		xRotLabel = new QLabel("X Rotation");
		rowTwoLayout->addWidget(xRotLabel);
		xRotSlider = new QSlider(Qt::Horizontal);
		rowTwoLayout->addWidget(xRotSlider);

	rowThreeLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	windowLayout->addLayout(rowThreeLayout);
		yRotLabel = new QLabel("Y Rotation");
		rowThreeLayout->addWidget(yRotLabel);
		yRotSlider = new QSlider(Qt::Horizontal);
		rowThreeLayout->addWidget(yRotSlider);

	rowFourLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	windowLayout->addLayout(rowFourLayout);
		zRotLabel = new QLabel("Z Rotation");
		rowFourLayout->addWidget(zRotLabel);
		zRotSlider = new QSlider(Qt::Horizontal);
		rowFourLayout->addWidget(zRotSlider);

	rowFiveLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	windowLayout->addLayout(rowFiveLayout);
		animationCheckBox = new QCheckBox("Animation Enabled");
		rowFiveLayout->addWidget(animationCheckBox);

		renderModeLabel = new QLabel("Render Mode");
		pointRadio = new QRadioButton("Points");
		lineRadio = new QRadioButton("Lines");
		triangleRadio = new QRadioButton("Triangles");
		rowFiveLayout->addWidget(renderModeLabel);
		rowFiveLayout->addWidget(pointRadio);
		rowFiveLayout->addWidget(lineRadio);
		rowFiveLayout->addWidget(triangleRadio);

	rowSixLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	windowLayout->addLayout(rowSixLayout);
		objectChooserLabel = new QLabel("Platonic Solid");
		rowSixLayout->addWidget(objectChooserLabel);
		objectChooser = new QComboBox();
		objectChooser->addItems(objectNameList);
		objectChooser->setCurrentIndex(INITIAL_OBJECT_INDEX);
		rowSixLayout->addWidget(objectChooser);

	rowSevenLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	windowLayout->addLayout(rowSevenLayout);
		colourLabel = new QLabel("Triangle Colours");
		rowSevenLayout->addWidget(colourLabel);
		colourChooser = new QComboBox();
		colourChooser->addItems(colourNameList);
		colourChooser->setCurrentIndex(INITIAL_COLOUR_INDEX);
		rowSevenLayout->addWidget(colourChooser);

	resetInterface();
}

GLWindow::~GLWindow()
{
	// Done in reverse-order, bottom of visual hierarchy to the top
	delete colourLabel;
	delete colourChooser;
	delete objectChooserLabel;
	delete objectChooser;
	delete animationCheckBox;
	delete xRotLabel;
	delete yRotLabel;
	delete zRotLabel;
	delete xRotSlider;
	delete yRotSlider;
	delete zRotSlider;
	delete canvasWidget;
	delete renderModeLabel;
	delete pointRadio;
	delete lineRadio;
	delete triangleRadio;
	delete rowOneLayout;
	delete rowTwoLayout;
	delete rowThreeLayout;
	delete rowFourLayout;
	delete rowFiveLayout;
	delete rowSixLayout;
	delete rowSevenLayout;
	delete windowLayout;
	delete actionQuit;
	delete fileMenu;
	delete menuBar;
}

void GLWindow::setDrawable(Drawable* newDrawable)
{
	drawable = newDrawable;
	// Also make sure the canvas widget knows about
	// the new drawable so it can be rendered
	canvasWidget->setDrawable(newDrawable);
}

void GLWindow::resetInterface()
{
	xRotSlider->setMinimum(0);
	xRotSlider->setMaximum(360);
	xRotSlider->setValue(drawable->xRotation());
	yRotSlider->setMinimum(0);
	yRotSlider->setMaximum(360);
	yRotSlider->setValue(drawable->yRotation());
	zRotSlider->setMinimum(0);
	zRotSlider->setMaximum(360);
	zRotSlider->setValue(drawable->zRotation());

	RenderMethod renderMethod = drawable->renderMethod();
	switch (renderMethod)
	{
	case RENDER_METHOD_POINTS:
		pointRadio->setChecked(true);
		break;
	case RENDER_METHOD_LINES:
		lineRadio->setChecked(true);
		break;
	case RENDER_METHOD_TRIANGLES:
		triangleRadio->setChecked(true);
		break;
	}

	update(); // force refresh
	canvasWidget->update(); // wasn't repainting with update()...
}


