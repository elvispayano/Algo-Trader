#ifndef DATABASE_CONTROLLER_H
#define DATABASE_CONTROLLER_H

// Forward Declarations
class Postgres;

class DatabaseController {
public:
  DatabaseController( void );
  ~DatabaseController( void );

  /// @fn     void initialize( void )
  /// @brief  Initialize the broker controller with the configured settings
  void initialize( void );

  /// @fn     void perform( void )
  /// @brief  Perform a database controller update
  void perform( void );

private:
  Postgres* pDatabase;
};

#endif /* DATABASE_CONTROLLER_H */
