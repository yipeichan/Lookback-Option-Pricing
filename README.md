# Option-Pricing
This repository contains programs to price Lookback Options with Monte Carlo Simulation and binomial tree framework<br>

<img width="1028" alt="screen shot 2018-10-27 at 3 25 23 pm" src="https://user-images.githubusercontent.com/24948460/47600998-97689680-d9fc-11e8-9015-bf8a6077b6c9.png">


q : annualized daily compounded dividend yield <br>

<small><foot> Reference: lecture notes of the course-- Financial Computation (graduate level)  </foot></small>


## Instruction
The payoff function of the lookback put is as follow <br>
Payoff<sub>t</sub> = max(S<sub>max,t</sub> − S<sub>t</sub>, 0), where S<sub>max,t</sub> = max S<sub>u</sub>, for u = 0, ∆t, 2∆t, ..., t
