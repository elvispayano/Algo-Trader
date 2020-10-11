#ifndef DATABASE_CONTROLLER_H
#define DATABASE_CONTROLLER_H

// Forward Declarations
class Postgres;
class DataServer;

class DatabaseController {
public:
  DatabaseController( DataServer* server );
  ~DatabaseController( void );

  /// @fn     void initialize( void )
  /// @brief  Initialize the broker controller with the configured settings
  void initialize( void );

  /// @fn     void perform( void )
  /// @brief  Perform a database controller update
  void perform( void );

private:
  DataServer* pServer;
  Postgres*   pDatabase;
};

#endif /* DATABASE_CONTROLLER_H */
