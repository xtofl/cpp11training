
#include <string>
#include <memory>
#include <vector>
#include <cstdio>
#include <boost/asio.hpp>
#include "di.hpp"

namespace di = boost::di;

namespace logging {
	class message {
		public:
			message(std::string developese)
				: developese(std::move(developese))
			{}
			std::string str() const { return developese; }
		private:
			std::string developese;
	};

	class IInfo {
		public:
			virtual ~IInfo() = default;
			virtual bool info(message);
	};

	class ITranslate {
		public:
			virtual ~ITranslate() = default;
	};

	class Logging {
		public:
			struct index { int i; };
			std::vector<message> messages() const { return messages_; }
			std::vector<message> messages(index begin, index end) const;
			void append(message m){
				messages_.push_back(std::move(m));
			}
			std::shared_ptr<ITranslate> tr;
		private:
			std::vector<message> messages_;
	};
}
namespace vehicle {
	class Engine {
		public:
			explicit Engine(
				std::shared_ptr<logging::Logging> logging
			) : logging(std::move(logging))
			{}
			void start(){
				logging->append({"started"});
			}
			void stop(){
				logging->append({"stopped"});
			}
		private:
			std::shared_ptr<logging::Logging> logging;
	};
	class Vehicle {
		public:
			virtual ~Vehicle() = default;
			virtual void start(){
			}
			virtual void stop(){
			}
	};
	class Car : public Vehicle {
		public:
			Car(
				std::unique_ptr<Engine> engine,
				std::shared_ptr<logging::Logging> logging)
			: engine(std::move(engine))
			, logging(std::move(logging))
			{}
		private:
			std::unique_ptr<Engine> engine;
			std::shared_ptr<logging::Logging> logging;
			void start() override {
				engine->start();
				logging->append({"started"});
			}
			void stop() override {
				engine->stop();
				logging->append({"stopped"});
			}
	};
}
namespace travel {
	class Journey {
		public:
			Journey(
				std::shared_ptr<vehicle::Vehicle> vehicle,
				std::shared_ptr<logging::Logging> logging
			)
			: vehicle(std::move(vehicle))
			, logging(std::move(logging))
			{
				this->logging->append({"Journey started"});
			}
			void make(std::string where) {
				vehicle->start();
				logging->append({"Going to " + where});
				vehicle->stop();
				logging->append({"Being at " + where});

				vehicle->start();
				logging->append({"Coming back from " + where});
				vehicle->stop();
			}
		private:
			std::shared_ptr<vehicle::Vehicle> vehicle;
			std::shared_ptr<logging::Logging> logging;
	};
}
int main() {

	auto injector = di::make_injector(
		di::bind<logging::Logging>.to(std::make_shared<logging::Logging>()),
		di::bind<vehicle::Vehicle>.to<vehicle::Car>()
	);
	auto logging = injector.create<std::shared_ptr<logging::Logging>>();
	logging->append(logging::message{"Logging started"});
	auto journey = injector.create<travel::Journey>();
	journey.make("Brussels");
	logging->append(logging::message{"Logging stopped"});

	for(const auto &m: logging->messages()) {
		puts(m.str().c_str());
		puts("\n");
	}
}
