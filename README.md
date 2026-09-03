# Feedforward Closedloop Learning (FCL)

[Forward propagation closed loop learning
Bernd Porr, Paul Miller. Adaptive Behaviour 2019.](https://journals.sagepub.com/doi/10.1177/1059712319851070)

[Submission version](https://www.berndporr.me.uk/Porr_Miller_FCL_2019_Adaptive_Behaviour.pdf)

## Error _forward_ propagation

![alt tag](closed_loop.png)

For an autonomous agent, the inputs are the sensory data that inform the agent of the state of the world, and the outputs are their actions, which act on the world and consequently produce new sensory inputs. The agent only knows of its own actions via their effect on future inputs; therefore desired states, and error signals, are most naturally defined in terms of the inputs. Most machine learning algorithms, however, operate in terms of desired outputs. For example, backpropagation takes target output values and propagates the corresponding error backwards through the network in order to change the weights. In closed loop settings, it is far more obvious how to define desired sensory inputs than desired actions, however. To train a deep network using errors defined in the input space would call for an algorithm that can propagate those errors _forwards_ through the network, from input layer to output layer, in much the same way that activations are propagated.

![alt tag](act_error_flow.png)

Comparison between FCL, backprop and ICO learning:

![alt tag](learning_units_comparison.png)

Note that the code here has been evolved from the original one. In order
to ensure stability the Oja rule is being applied on neuron level.

## Prerequisites (Linux)

Ubuntu LTS with swig installed.

## How to compile / install?

### From source under Linux (C++ and Python)
```
      cmake .
      make
      sudo make install
      ./setup.py install --user
```

## Demos

A classic line follower demo in [linefollower/](linefollower)`

## Unit tests

There are various unit tests for the neurons, layers and FCL itself. Run
them by typing:
```
make test
```

## Class reference

The online documentation can be found here: https://berndporr.github.io/feedforward_closedloop_learning/

## License

GNU GENERAL PUBLIC LICENSE

Version 3, 29 June 2007

```
(C) 2017-2022, Bernd Porr <bernd@glasgowneuro.tech>
(C) 2017,2018, Paul Miller <paul@glasgowneuro.tech>
```

## DOI of the Code

[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.7451257.svg)](https://doi.org/10.5281/zenodo.7451257)
