#ifndef DATABASE_CONTROLLER_H
#define DATABASE_CONTROLLER_H

class DatabaseController {
public:
  DatabaseController( void );
  ~DatabaseController( void );

  void perform( void );

private:
  void processInputs( void ) {}
  void update( void ) {}
  void processOutputs( void ) {}
};

#endif /* DATABASE_CONTROLLER_H */
