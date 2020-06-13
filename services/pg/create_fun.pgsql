CREATE FUNCTION public.network_count()
    RETURNS bigint
    LANGUAGE 'sql'
    
AS $BODY$ SELECT COUNT(*) FROM networks $BODY$;

ALTER FUNCTION public.network_count()
    OWNER TO postgres;

/*

Sample function usage
//SELECT FROM insert_network('MSFT');

//SELECT * FROM network_count();

*/
