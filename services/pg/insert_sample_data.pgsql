/* Networks Table Sample Data Input */
INSERT INTO networks (TICKER, LAYERS) VALUES ('MSFT', 3);
INSERT INTO networks (TICKER, LAYERS) VALUES ('LMT', 2);

/* Layers Table Sample Data Input */
INSERT INTO layers (TICKER, LAYER_NUM, INPUTS, NODES, IND_START, LAYER_TYPE, ACT_TYPE)
    VALUES('MSFT', 1, 3, 2, 1, 0, 2);

/* Weight & Biases Table Sample Data Input */
INSERT INTO weights_biases (TICKER, INDEX, VALUE) VALUES ('MSFT', 1, 1.5);
INSERT INTO weights_biases (TICKER, INDEX, VALUE) VALUES ('MSFT', 2, 2.5);
INSERT INTO weights_biases (TICKER, INDEX, VALUE) VALUES ('MSFT', 3, 3.5);
INSERT INTO weights_biases (TICKER, INDEX, VALUE) VALUES ('MSFT', 4, 4.5);
INSERT INTO weights_biases (TICKER, INDEX, VALUE) VALUES ('MSFT', 5, 5.5);
INSERT INTO weights_biases (TICKER, INDEX, VALUE) VALUES ('MSFT', 6, 6.5);
INSERT INTO weights_biases (TICKER, INDEX, VALUE) VALUES ('MSFT', 7, 7.5);
INSERT INTO weights_biases (TICKER, INDEX, VALUE) VALUES ('MSFT', 8, 8.5);
