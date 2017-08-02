#include <iostream>
#include <vector>

namespace tf {

}

class LevelsetUniform2D;
class NumpyArray;

int main()
{
	using namespace std;
	using namespace tf;

	vector<LevelsetUniform2D*> lsv, lsv_recon, lsv_interpolated; // some levelsets to train

	NumpyArray x_data = NumpyArray::from_levelset(lsv);

	Autoencoder ae(x_data, "AE_conv_201708011.py");
	
	while (true)
	{
		ae.train_self_copy(x_data);

		NumpyArray z_data = ae.get_z(x_data);
		NumpyArray z_input = ae.get_z_samples_between(z_data[0], z_data[1], num_samples = 10);
		NumpyArray y_out_from_z = ae.get_y_from_z(z_input);

		ae.train_self_copy(y_out_from_z); // train encoder and apply self similarity

		NumpyArray y_out_from_x = ae.y_from_x(y_out_from_z);

		NumpyArray d_volume = NumpyArray::from_levelset_volume(to_levelset(y_out_from_x));
		ae.train_d_volume(y_out_from_z, d_volume, training_options);
		ae.train_d_volume_loss(z_input, target_v = 1.0); // train decoder so that it's output ys' volume = 1 
	}

	visualize_levelset(lsv_recon);

	return 0;
}

