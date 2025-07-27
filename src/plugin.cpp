#include "plugin.hpp"


Plugin* pluginInstance;
std::vector<std::shared_ptr<Svg>> quantSvgCache;
std::vector<std::shared_ptr<Svg>> compSvgCache;
std::vector<std::shared_ptr<Svg>> opSvgCache;
std::vector<std::shared_ptr<Svg>> boolSvgCache;


void init(Plugin* p) {
	pluginInstance = p;
	p->addModel(modelOctoplus);


	// Add modules here
	// p->addModel(modelMyModule);

	// Any other plugin initialization may go here.
	/*if(!APP || !APP->window) {
		return;
	}*/

	quantSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/quant_sprites/a_qsprite.svg")));
	quantSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/quant_sprites/b_msprite.svg")));
	quantSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/quant_sprites/c_dmsprite.svg")));
	quantSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/quant_sprites/d_d2msprite.svg")));
	quantSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/quant_sprites/e_ssprite.svg")));
	quantSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/quant_sprites/f_dssprite.svg")));
	quantSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/quant_sprites/g_d2ssprite.svg")));
	quantSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/quant_sprites/h_asprite.svg")));
	quantSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/quant_sprites/i_dasprite.svg")));
	quantSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/quant_sprites/j_d2asprite.svg")));
	quantSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/quant_sprites/k_bsprite.svg")));
	quantSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/quant_sprites/l_dbsprite.svg")));
	quantSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/quant_sprites/m_d2bsprite.svg")));
	quantSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/basesprite.svg"))); //load as sentinel in case of lag, indexing out will crash vcv

	compSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/comp_sprites/n_csprite.svg")));
	compSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/comp_sprites/o_eqsprite.svg")));
	compSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/comp_sprites/p_neqsprite.svg")));
	compSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/comp_sprites/q_gtsprite.svg")));
	compSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/comp_sprites/r_ltsprite.svg")));
	compSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/comp_sprites/s_gtesprite.svg")));
	compSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/comp_sprites/t_ltesprite.svg")));
	compSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/basesprite.svg"))); 

	opSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/op_sprites/osprite.svg")));
	opSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/op_sprites/plus_sprite.svg")));
	opSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/op_sprites/minus_sprite.svg")));
	opSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/op_sprites/mult_sprite.svg")));
	opSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/op_sprites/div_sprite.svg")));
	opSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/op_sprites/pow_sprite.svg")));
	opSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/op_sprites/alogb_sprite.svg")));
	opSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/op_sprites/sin_sprite.svg")));
	opSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/op_sprites/cos_sprite.svg")));
	opSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/op_sprites/tan_sprite.svg")));
	opSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/op_sprites/inverse_sin_sprite.svg")));
	opSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/op_sprites/inverse_cos_sprite.svg")));
	opSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/op_sprites/inverse_tan_sprite.svg")));
	opSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/basesprite.svg"))); 

	boolSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/bool_sprites/bsprite.svg")));
	boolSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/bool_sprites/and_sprite.svg")));
	boolSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/bool_sprites/or_sprite.svg")));
	boolSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/bool_sprites/unless_sprite.svg")));
	boolSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/bool_sprites/nand_sprite.svg")));
	boolSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/bool_sprites/nor_sprite.svg")));
	boolSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/bool_sprites/xor_sprite.svg")));
	boolSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/bool_sprites/xnor_sprite.svg")));
	boolSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/bool_sprites/implication_sprite.svg")));
	boolSvgCache.push_back(APP->window->loadSvg(asset::plugin(pluginInstance, "res/basesprite.svg")));

	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}
