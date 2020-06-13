/* Networks Table Sample Data Input */
INSERT INTO networks (TICKER, LAYERS) VALUES ('MSFT', 3);
INSERT INTO networks (TICKER, LAYERS) VALUES ('LMT', 2);

/* Layers Table Sample Data Input */
INSERT INTO layers (TICKER, LAYER_NUM, INPUTS, NODES, IND_START, LAYER_TYPE, ACT_TYPE)
    VALUES('MSFT', 1, 1, 1, 1, 1, 2);

/* Weight & Biases Table Sample Data Input */
INSERT INTO weights_biases (TICKER, INDEX, VALUE) VALUES ('MSFT', 1, 2.5);
