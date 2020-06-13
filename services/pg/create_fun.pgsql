CREATE FUNCTION public.network_count()
    RETURNS bigint
    LANGUAGE 'sql'
    
AS $BODY$ SELECT COUNT(*) FROM networks $BODY$;

ALTER FUNCTION public.network_count()
    OWNER TO postgres;


CREATE FUNCTION public.get_network(IN req_id integer)
    RETURNS text
    LANGUAGE 'sql'
    
AS $BODY$SELECT TICKER FROM networks WHERE ID = req_id$BODY$;

ALTER FUNCTION public.get_network(integer)
    OWNER TO postgres;
/*

Sample function usage
//SELECT FROM insert_network('MSFT');

//SELECT * FROM network_count();

*/
