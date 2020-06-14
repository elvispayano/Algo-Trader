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

/* Create Layer Inputs Function*/
CREATE FUNCTION public.layer_inputs(IN tick text, IN layer integer)
    RETURNS integer
    LANGUAGE 'sql'
    
AS $BODY$ SELECT INPUTS FROM layers WHERE TICKER = tick AND LAYER_NUM = layer$BODY$;

/* Create Layer Nodes Function*/
CREATE FUNCTION public.layer_nodes(IN tick text, IN layer integer)
    RETURNS integer
    LANGUAGE 'sql'
    
AS $BODY$ SELECT NODES FROM layers WHERE TICKER = tick AND LAYER_NUM = layer$BODY$;

/* Create Layer Ind Function*/
CREATE FUNCTION public.layer_ind(IN tick text, IN layer integer)
    RETURNS integer
    LANGUAGE 'sql'
    
AS $BODY$ SELECT IND_START FROM layers WHERE TICKER = tick AND LAYER_NUM = layer$BODY$;

/* Create Layer Type Function*/
CREATE FUNCTION public.layer_type(IN tick text, IN layer integer)
    RETURNS integer
    LANGUAGE 'sql'
    
AS $BODY$ SELECT LAYER_TYPE FROM layers WHERE TICKER = tick AND LAYER_NUM = layer$BODY$;

/* Create Layer Activation Function*/
CREATE FUNCTION public.layer_activation(IN tick text, IN layer integer)
    RETURNS integer
    LANGUAGE 'sql'
    
AS $BODY$ SELECT ACT_TYPE FROM layers WHERE TICKER = tick AND LAYER_NUM = layer$BODY$;

/* Create Get WB Function*/
CREATE FUNCTION public.get_wb(IN tick text, IN ind integer)
    RETURNS real
    LANGUAGE 'sql'
    
AS $BODY$ SELECT VALUE FROM weights_biases WHERE TICKER = tick AND INDEX = ind$BODY$;

/*

Sample function usage
//SELECT FROM insert_network('MSFT');

//SELECT * FROM network_count();

*/
