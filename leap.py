FEATURES_LEN = 768
HAND_DATA_LEN = 60

#TODO
#init here
#END
	
def get_hand_data(*image_features):
	hand_data = [0] * HAND_DATA_LEN
	
	#TODO
	for i in range(HAND_DATA_LEN):
		hand_data[i] = image_features[i]
	#END
	
	return hand_data
