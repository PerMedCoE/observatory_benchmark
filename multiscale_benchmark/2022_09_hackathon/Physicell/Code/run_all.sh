make reset && make clean && make single_diffusion && make -j4
./project << single_diffusion.log
make reset && make clean && make many_diffusion && make -j4
./project << many_diffusion.log
make reset && make clean && make mechanics_movement && make -j4
./project << mechanics_movement.log
make reset && make clean && make mechanics_pushing && make -j4
./project << mechanics_pushing.log
make reset && make clean && make fixed_cell_cycle && make -j4
./project << fixed_cell_cycle.log
make reset && make clean && make stochastic_cell_cylcle && make -j4
./project << stochastic_cell_cylcle.log