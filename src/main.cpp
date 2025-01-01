#include <QApplication>

#include "Controller.hpp"
#include "MainWindow.hpp"

// TODO :
// * Ajouter bouton "Connect" a cote du tty + baud rate choisi
//      * Desactiver bloc command et monitoring entre temps
// * Ajouter bouton "Disconnect"
// * Connexion etablie : 1 thread pour envoyer , 1 thread pour monitorer la
// reception => 2 open ?

int main(int argc, char *argv[]) {
  // Initialize the Qt application
  QApplication app(argc, argv);

  // Create the main window of the application
  MainWindow mainWindow;

  // Create the controller, passing the MainWindow (view) as the controller's
  // view
  Controller controller(&mainWindow);

  // Show the main window of the application
  mainWindow.show();

  // Start the Qt event loop
  return app.exec();
}