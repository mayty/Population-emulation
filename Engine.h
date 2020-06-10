#pragma once
#include "Window.h"
#include "StartData.h"
#include "Scene.h"
#include <unordered_map>
#include <memory>
#include <ctime>

namespace mns
{
	class engine
	{
		Window window;
		int default_state;
		int exit_state;

		std::unordered_map<int, std::unique_ptr<Scene>> scenes;

	public:
		engine();
		static std::string get_last_error();
		template<class Scene_der>
		void add_scene(int key, const Scene_der& scene);
		template<class Scene_der>
		void add_scene(int key, Scene_der&& scene);
		void set_default_state(int state);
		void set_exit_state(int state);
		template<class Save_scene, int save_state, int load_state>
		void run(const int save_key);
		~engine();
	};

	template<class Scene_der>
	inline void engine::add_scene(int key, const Scene_der& scene)
	{
		if (scenes.find(key) != scenes.end())
		{
			throw std::exception{};
		}
		scenes.insert({ key, std::make_unique<Scene_der>(scene) });
	}

	template<class Scene_der>
	inline void engine::add_scene(int key, Scene_der&& scene)
	{
		if (scenes.find(key) != scenes.end())
		{
			throw std::exception{};
		}
		scenes.insert({ key, std::make_unique<Scene_der>(scene) });
	}

	template<class Save_scene, int save_state, int load_state>
	inline void engine::run(const int save_key)
	{
		if (!window.fine())
		{
			throw std::exception{};
		}
		if (scenes.find(save_key) == scenes.end())
		{
			throw std::exception{};
		}
		srand(time(NULL));
		StartData data;
		int returnValue = default_state;
		int last_value = default_state;
		Save_scene save;

		while (returnValue != exit_state)
		{
			switch (returnValue)
			{
			case save_state:
				save = *dynamic_cast<Save_scene*>(scenes.at(save_key).get());
				returnValue = last_value;
				break;
			case load_state:
				scenes.insert_or_assign(last_value, std::make_unique<Save_scene>(save));
				returnValue = last_value;
				break;
			default:
				if (scenes.find(returnValue) == scenes.end())
				{
					if (returnValue == default_state)
					{
						throw std::exception{};
					}
					returnValue = default_state;
					last_value = default_state;
				}
				else
				{
					last_value = returnValue;
					returnValue = scenes.at(returnValue)->Run(window, data);
				}
			}
		}
	}
}
