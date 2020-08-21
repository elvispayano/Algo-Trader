/*
  Title:
    IB Wrapper

  Description:
    This class is responsible for configuring and establishing the
    connection to the TWS platform. The main object of this class is
    to ensure that when a request of API call is made, there is a
    valid connection.

  Author:
    Interactive Broker
*/

#ifndef IB_WRAPPER_H
#define IB_WRAPPER_H

// Utility Includes
#include "stock.h"

// Standard Includes
#include <map>
#include <queue>
#include <string>

// Interactive Broker Includes
#include "EReader.h"
#include "EReaderOSSignal.h"
#include "EWrapper.h"
#include "Order.h"

class EClientSocket;

enum State {
  ST_CONNECT,
  ST_TICKDATAOPERATION,
  ST_TICKDATAOPERATION_ACK,
  ST_TICKOPTIONCOMPUTATIONOPERATION,
  ST_TICKOPTIONCOMPUTATIONOPERATION_ACK,
  ST_DELAYEDTICKDATAOPERATION,
  ST_DELAYEDTICKDATAOPERATION_ACK,
  ST_MARKETDEPTHOPERATION,
  ST_MARKETDEPTHOPERATION_ACK,
  ST_REALTIMEBARS,
  ST_REALTIMEBARS_ACK,
  ST_MARKETDATATYPE,
  ST_MARKETDATATYPE_ACK,
  ST_HISTORICALDATAREQUESTS,
  ST_HISTORICALDATAREQUESTS_ACK,
  ST_OPTIONSOPERATIONS,
  ST_OPTIONSOPERATIONS_ACK,
  ST_CONTRACTOPERATION,
  ST_CONTRACTOPERATION_ACK,
  ST_MARKETSCANNERS,
  ST_MARKETSCANNERS_ACK,
  ST_FUNDAMENTALS,
  ST_FUNDAMENTALS_ACK,
  ST_BULLETINS,
  ST_BULLETINS_ACK,
  ST_ACCOUNTOPERATIONS,
  ST_ACCOUNTOPERATIONS_ACK,
  ST_ORDEROPERATIONS,
  ST_ORDEROPERATIONS_ACK,
  ST_OCASAMPLES,
  ST_OCASAMPLES_ACK,
  ST_CONDITIONSAMPLES,
  ST_CONDITIONSAMPLES_ACK,
  ST_BRACKETSAMPLES,
  ST_BRACKETSAMPLES_ACK,
  ST_HEDGESAMPLES,
  ST_HEDGESAMPLES_ACK,
  ST_TESTALGOSAMPLES,
  ST_TESTALGOSAMPLES_ACK,
  ST_FAORDERSAMPLES,
  ST_FAORDERSAMPLES_ACK,
  ST_FAOPERATIONS,
  ST_FAOPERATIONS_ACK,
  ST_DISPLAYGROUPS,
  ST_DISPLAYGROUPS_ACK,
  ST_MISCELANEOUS,
  ST_MISCELANEOUS_ACK,
  ST_CANCELORDER,
  ST_CANCELORDER_ACK,
  ST_FAMILYCODES,
  ST_FAMILYCODES_ACK,
  ST_SYMBOLSAMPLES,
  ST_SYMBOLSAMPLES_ACK,
  ST_REQMKTDEPTHEXCHANGES,
  ST_REQMKTDEPTHEXCHANGES_ACK,
  ST_REQNEWSTICKS,
  ST_REQNEWSTICKS_ACK,
  ST_REQSMARTCOMPONENTS,
  ST_REQSMARTCOMPONENTS_ACK,
  ST_NEWSPROVIDERS,
  ST_NEWSPROVIDERS_ACK,
  ST_REQNEWSARTICLE,
  ST_REQNEWSARTICLE_ACK,
  ST_REQHISTORICALNEWS,
  ST_REQHISTORICALNEWS_ACK,
  ST_REQHEADTIMESTAMP,
  ST_REQHEADTIMESTAMP_ACK,
  ST_REQHISTOGRAMDATA,
  ST_REQHISTOGRAMDATA_ACK,
  ST_REROUTECFD,
  ST_REROUTECFD_ACK,
  ST_MARKETRULE,
  ST_MARKETRULE_ACK,
  ST_PNL,
  ST_PNL_ACK,
  ST_PNLSINGLE,
  ST_PNLSINGLE_ACK,
  ST_CONTFUT,
  ST_CONTFUT_ACK,
  ST_PING,
  ST_PING_ACK,
  ST_REQHISTORICALTICKS,
  ST_REQHISTORICALTICKS_ACK,
  ST_REQTICKBYTICKDATA,
  ST_REQTICKBYTICKDATA_ACK,
  ST_WHATIFSAMPLES,
  ST_WHATIFSAMPLES_ACK,
  ST_IDLE
};

class IBWrapper : public EWrapper {
public:
  IBWrapper( std::string host, int port, int clientID );
  ~IBWrapper( void );

  // Required Interface Functions
  virtual void processMessages( void );

  virtual bool  connect( void );
  virtual void  disconnect( void );
  bool          isConnected( void ) const;
  virtual bool  responseReady( void ) { return !responseMessage.empty(); }
  virtual Stock getResponse( void );

  virtual void getCurrentPrice( std::string ticker );
  virtual void
               orderMarket( std::string ticker, std::string action, double quantity );
  virtual void orderLimit( std::string ticker,
                           std::string action,
                           double      quantity,
                           double      price );
  virtual void orderStop( std::string ticker,
                          std::string action,
                          double      quantity,
                          double      price );

private:
  void clearOrder( void );
  void clearContract( void );

  Stock       data;
  bool        listening;
  std::string host;
  int         port, clientID, validID;

  Contract contractRequest;
  Order    orderRequest;

  std::queue< Stock >          responseMessage;
  std::map< int, std::string > updateMap;

protected:
  //![socket_declare]
  EReaderOSSignal      Signal;
  EClientSocket* const pClient;

  //! [socket_declare]
  State  m_state;
  time_t m_sleepDeadline;

  EReader*    pReader;
  bool        m_extraAuth;
  std::string m_bboExchange;

  void pnlOperation( void ) {}
  void pnlSingleOperation( void ) {}
  void tickDataOperation( void ) {}
  void tickOptionComputationOperation( void ) {}
  void delayedTickDataOperation( void ) {}
  void marketDepthOperations( void ) {}
  void realTimeBars( void ) {}
  void marketDataType( void ) {}
  void historicalDataRequests( void ) {}
  void optionsOperations( void ) {}
  void accountOperations( void ) {}
  void orderOperations( void ) {}
  void ocaSamples( void ) {}
  void conditionSamples( void ) {}
  void bracketSample( void ) {}
  void hedgeSample( void ) {}
  void contractOperations( void ) {}
  void marketScanners( void ) {}
  void fundamentals( void ) {}
  void bulletins( void ) {}
  void testAlgoSamples( void ) {}
  void financialAdvisorOrderSamples( void ) {}
  void financialAdvisorOperations( void ) {}
  void testDisplayGroups( void ) {}
  void miscelaneous( void ) {}
  void reqFamilyCodes( void ) {}
  void reqMatchingSymbols( void ) {}
  void reqMktDepthExchanges( void ) {}
  void reqNewsTicks( void ) {}
  void reqSmartComponents( void ) {}
  void reqNewsProviders( void ) {}
  void reqNewsArticle( void ) {}
  void reqHistoricalNews( void ) {}
  void reqHeadTimestamp( void ) {}
  void reqHistogramData( void ) {}
  void rerouteCFDOperations( void ) {}
  void marketRuleOperations( void ) {}
  void continuousFuturesOperations( void ) {}
  void reqHistoricalTicks( void ) {}
  void reqTickByTickData( void ) {}
  void whatIfSamples( void ) {}

  void reqCurrentTime( void ) {}

  void printContractMsg( const Contract& contract );
  void printContractDetailsMsg( const ContractDetails& contractDetails );
  void printContractDetailsSecIdList( const TagValueListSPtr& secIdList );
  void printBondContractDetailsMsg( const ContractDetails& contractDetails );

  void tickPrice( TickerId          tickerId,
                  TickType          field,
                  double            price,
                  const TickAttrib& attrib ) override;
  void tickSize( TickerId tickerId, TickType field, int size ) override;
  void tickOptionComputation( TickerId tickerId,
                              TickType tickType,
                              double   impliedVol,
                              double   delta,
                              double   optPrice,
                              double   pvDividend,
                              double   gamma,
                              double   vega,
                              double   theta,
                              double   undPrice ) override;
  void
       tickGeneric( TickerId tickerId, TickType tickType, double value ) override;
  void tickString( TickerId           tickerId,
                   TickType           tickType,
                   const std::string& value ) override;
  void tickEFP( TickerId           tickerId,
                TickType           tickType,
                double             basisPoints,
                const std::string& formattedBasisPoints,
                double             totalDividends,
                int                holdDays,
                const std::string& futureLastTradeDate,
                double             dividendImpact,
                double             dividendsToLastTradeDate ) override;
  void orderStatus( OrderId            orderId,
                    const std::string& status,
                    double             filled,
                    double             remaining,
                    double             avgFillPrice,
                    int                permId,
                    int                parentId,
                    double             lastFillPrice,
                    int                clientId,
                    const std::string& whyHeld,
                    double             mktCapPrice ) override;
  void openOrder( OrderId orderId,
                  const Contract&,
                  const Order&,
                  const OrderState& ) override;
  void openOrderEnd() override;
  void winError( const std::string& str, int lastError ) override;
  void connectionClosed() override;
  void updateAccountValue( const std::string& key,
                           const std::string& val,
                           const std::string& currency,
                           const std::string& accountName ) override;
  void updatePortfolio( const Contract&    contract,
                        double             position,
                        double             marketPrice,
                        double             marketValue,
                        double             averageCost,
                        double             unrealizedPNL,
                        double             realizedPNL,
                        const std::string& accountName ) override;
  void updateAccountTime( const std::string& timeStamp ) override;
  void accountDownloadEnd( const std::string& accountName ) override;
  void nextValidId( OrderId orderId ) override;
  void contractDetails( int                    reqId,
                        const ContractDetails& contractDetails ) override;
  void bondContractDetails( int                    reqId,
                            const ContractDetails& contractDetails ) override;
  void contractDetailsEnd( int reqId ) override;
  void execDetails( int              reqId,
                    const Contract&  contract,
                    const Execution& execution ) override;
  void execDetailsEnd( int reqId ) override;
  void error( int id, int errorCode, const std::string& errorString ) override;
  void updateMktDepth( TickerId id,
                       int      position,
                       int      operation,
                       int      side,
                       double   price,
                       int      size ) override;
  void updateMktDepthL2( TickerId           id,
                         int                position,
                         const std::string& marketMaker,
                         int                operation,
                         int                side,
                         double             price,
                         int                size,
                         bool               isSmartDepth ) override;
  void updateNewsBulletin( int                msgId,
                           int                msgType,
                           const std::string& newsMessage,
                           const std::string& originExch ) override;
  void managedAccounts( const std::string& accountsList ) override;
  void receiveFA( faDataType pFaDataType, const std::string& cxml ) override;
  void historicalData( TickerId reqId, const Bar& bar ) override;
  void historicalDataEnd( int                reqId,
                          const std::string& startDateStr,
                          const std::string& endDateStr ) override;
  void scannerParameters( const std::string& xml ) override;
  void scannerData( int                    reqId,
                    int                    rank,
                    const ContractDetails& contractDetails,
                    const std::string&     distance,
                    const std::string&     benchmark,
                    const std::string&     projection,
                    const std::string&     legsStr ) override;
  void scannerDataEnd( int reqId ) override;
  void realtimeBar( TickerId reqId,
                    long     time,
                    double   open,
                    double   high,
                    double   low,
                    double   close,
                    long     volume,
                    double   wap,
                    int      count ) override;
  void currentTime( long time ) override;
  void fundamentalData( TickerId reqId, const std::string& data ) override;
  void deltaNeutralValidation(
      int reqId, const DeltaNeutralContract& deltaNeutralContract ) override;
  void tickSnapshotEnd( int reqId ) override;
  void marketDataType( TickerId reqId, int marketDataType ) override;
  void commissionReport( const CommissionReport& commissionReport ) override;
  void position( const std::string& account,
                 const Contract&    contract,
                 double             position,
                 double             avgCost ) override;
  void positionEnd() override;
  void accountSummary( int                reqId,
                       const std::string& account,
                       const std::string& tag,
                       const std::string& value,
                       const std::string& curency ) override;
  void accountSummaryEnd( int reqId ) override;
  void verifyMessageAPI( const std::string& apiData ) override;
  void verifyCompleted( bool               isSuccessful,
                        const std::string& errorText ) override;
  void displayGroupList( int reqId, const std::string& groups ) override;
  void displayGroupUpdated( int                reqId,
                            const std::string& contractInfo ) override;
  void verifyAndAuthMessageAPI( const std::string& apiData,
                                const std::string& xyzChallange ) override;
  void verifyAndAuthCompleted( bool               isSuccessful,
                               const std::string& errorText ) override;
  void connectAck() override;
  void positionMulti( int                reqId,
                      const std::string& account,
                      const std::string& modelCode,
                      const Contract&    contract,
                      double             pos,
                      double             avgCost ) override;
  void positionMultiEnd( int reqId ) override;
  void accountUpdateMulti( int                reqId,
                           const std::string& account,
                           const std::string& modelCode,
                           const std::string& key,
                           const std::string& value,
                           const std::string& currency ) override;
  void accountUpdateMultiEnd( int reqId ) override;
  void securityDefinitionOptionalParameter(
      int                            reqId,
      const std::string&             exchange,
      int                            underlyingConId,
      const std::string&             tradingClass,
      const std::string&             multiplier,
      const std::set< std::string >& expirations,
      const std::set< double >&      strikes ) override;
  void securityDefinitionOptionalParameterEnd( int reqId ) override;
  void softDollarTiers( int                                  reqId,
                        const std::vector< SoftDollarTier >& tiers ) override;
  void familyCodes( const std::vector< FamilyCode >& familyCodes ) override;
  void symbolSamples(
      int                                       reqId,
      const std::vector< ContractDescription >& contractDescriptions ) override;
  void mktDepthExchanges( const std::vector< DepthMktDataDescription >&
                              depthMktDataDescriptions ) override;
  void tickNews( int                tickerId,
                 time_t             timeStamp,
                 const std::string& providerCode,
                 const std::string& articleId,
                 const std::string& headline,
                 const std::string& extraData ) override;
  void smartComponents( int reqId, const SmartComponentsMap& theMap ) override;
  void tickReqParams( int                tickerId,
                      double             minTick,
                      const std::string& bboExchange,
                      int                snapshotPermissions ) override;
  void
       newsProviders( const std::vector< NewsProvider >& newsProviders ) override;
  void newsArticle( int                requestId,
                    int                articleType,
                    const std::string& articleText ) override;
  void historicalNews( int                requestId,
                       const std::string& time,
                       const std::string& providerCode,
                       const std::string& articleId,
                       const std::string& headline ) override;
  void historicalNewsEnd( int requestId, bool hasMore ) override;
  void headTimestamp( int reqId, const std::string& headTimestamp ) override;
  void histogramData( int reqId, const HistogramDataVector& data ) override;
  void historicalDataUpdate( TickerId reqId, const Bar& bar ) override;
  void rerouteMktDataReq( int                reqId,
                          int                conid,
                          const std::string& exchange ) override;
  void rerouteMktDepthReq( int                reqId,
                           int                conid,
                           const std::string& exchange ) override;
  void
       marketRule( int                                  marketRuleId,
                   const std::vector< PriceIncrement >& priceIncrements ) override;
  void pnl( int    reqId,
            double dailyPnL,
            double unrealizedPnL,
            double realizedPnL ) override;
  void pnlSingle( int    reqId,
                  int    pos,
                  double dailyPnL,
                  double unrealizedPnL,
                  double realizedPnL,
                  double value ) override;
  void historicalTicks( int                                  reqId,
                        const std::vector< HistoricalTick >& ticks,
                        bool                                 done ) override;
  void historicalTicksBidAsk( int                                        reqId,
                              const std::vector< HistoricalTickBidAsk >& ticks,
                              bool done ) override;
  void historicalTicksLast( int                                      reqId,
                            const std::vector< HistoricalTickLast >& ticks,
                            bool done ) override;
  void tickByTickAllLast( int                   reqId,
                          int                   tickType,
                          time_t                time,
                          double                price,
                          int                   size,
                          const TickAttribLast& tickAttribLast,
                          const std::string&    exchange,
                          const std::string&    specialConditions ) override;
  void tickByTickBidAsk( int                     reqId,
                         time_t                  time,
                         double                  bidPrice,
                         double                  askPrice,
                         int                     bidSize,
                         int                     askSize,
                         const TickAttribBidAsk& tickAttribBidAsk ) override;
  void tickByTickMidPoint( int reqId, time_t time, double midPoint ) override;
  void
       orderBound( long long orderId, int apiClientId, int apiOrderId ) override;
  void completedOrder( const Contract&   contract,
                       const Order&      order,
                       const OrderState& orderState ) override;
  void completedOrdersEnd() override;
};

#endif /* IB_WRAPPER_H */
