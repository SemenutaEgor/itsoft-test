#include <iostream>
#include <pugixml.hpp>

int main() {
    pugi::xml_document doc;

    if (doc.load_file("../../test_config.xml").status != pugi::xml_parse_status::status_ok) {
        std::cerr << "Error: Configuration file not found" << std::endl;
        return 1;
    }

    auto root = doc.child("ControlSystem");
    
    if (root.empty()) {
        std::cerr << "Error: Root node <ControlSystem> not found" << std::endl;
        return 1;
    }

    auto ports = root.child("Ports");

    if (ports.empty()) {
        std::cerr << "Error: Node <Ports> not found" << std::endl;
        return 1;
    }

    for (auto& port : ports.children("Port")) {
        std::cout << "Port ID=\"" << port.attribute("ID").value() << "\"" << std::endl;
        std::cout << "  Up:" << port.child("Up").child_value() << std::endl;
        std::cout << "  AutoNegotiationEnabled:" << port.child("AutoNegotiationEnabled").child_value() << std::endl;
        std::cout << "  AllowedSpeed_10M" << port.child("AllowedSpeed_10M").child_value() << std::endl;
        std::cout << "  AllowedSpeed_100M" << port.child("AllowedSpeed_100M").child_value() << std::endl;
        std::cout << "  AllowedSpeed_1G" << port.child("AllowedSpeed_1G").child_value() << std::endl;
        std::cout << "  AllowedSpeed_10G" << port.child("AllowedSpeed_10G").child_value() << std::endl;
    }

    return 0;
}
