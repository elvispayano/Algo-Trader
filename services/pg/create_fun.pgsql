/* Create Network Count Function*/
CREATE FUNCTION public.network_count()
    RETURNS bigint
    LANGUAGE 'sql'
    
AS $BODY$ SELECT COUNT(*) FROM networks $BODY$;

/* Create Get Network Function*/
CREATE FUNCTION public.get_network(IN req_id integer)
    RETURNS text
    LANGUAGE 'sql'
    
AS $BODY$SELECT TICKER FROM networks WHERE ID = req_id$BODY$;

/* Create Network Expected Layers Function*/
CREATE FUNCTION public.layer_count(IN tick text)
    RETURNS integer
    LANGUAGE 'sql'
    
AS $BODY$ SELECT LAYERS FROM networks WHERE TICKER = tick$BODY$;


/*

Sample function usage
//SELECT FROM insert_network('MSFT');

//SELECT * FROM network_count();

*/
