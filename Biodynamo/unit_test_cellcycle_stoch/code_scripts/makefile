
run:
		@echo " "
		@echo " *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** "
		@echo " *** ensure the BioDynaMo file: 'BIODYNAMO_INSTALLATION_PATH/bin/thisbdm.sh' has been sourced first! *** "
		@echo " *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** "
		@echo " "
		biodynamo clean; \
		rm -rf ../new_results/output/; \
		biodynamo run && mv ./output ../new_results/
