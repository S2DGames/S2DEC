#pragma once

#include <string>
using std::string;

namespace S2D{

	class Component{
	private:
		const string type;

	public:
		Component() : type("NO TYPE"){

		}

		Component(string type) : type(type){
			
		}

		const string getType(){
			return type;
		}

		virtual const bool hasPosition(){
			return false;
		}

		virtual const bool hasControls(){
			return false;
		}

		virtual const bool hasSize(){
			return false;
		}

		virtual const bool hasImage(){
			return false;
		}

		virtual void onStart(){

		}

		virtual bool update(){
			return false;
		}
	};

}