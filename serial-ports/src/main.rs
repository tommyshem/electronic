extern crate serialport as serial_port;
use serial_port::{available_ports, SerialPort, SerialPortType};
use std::io::{self, Write};
use std::time::Duration;
use structopt::StructOpt;

#[derive(StructOpt, Debug)]
#[structopt(name = "serial-com")]
/// An example of StructOpt usage.
struct Opt {
    #[structopt(short, long)]
    /// Show a list of serial ports
    list: bool,

    #[structopt(short, long)]
    /// Debug mode for this command
    debug: bool,

    #[structopt(short, long, default_value = "115200")]
    /// Set baud rate speed
    baud: u32,

    #[structopt(short, long, default_value = "/dev/ttyUSB0")] // "/dev/ttyACM0")]
    /// Set port to use
    port: String,
}

fn main() {
    // parse command prompt args
    let opt = Opt::from_args();
    if opt.debug {
        println!("{:?}", opt);
    }
    // list com ports if --list is passed
    if opt.list {
        com_list_info()
    } else {
        let port_builder =
            serial_port::new(opt.port.as_str(), opt.baud).timeout(Duration::from_millis(10));
        if opt.debug {
            print!("Serial Port Builder Info \n{:#?}", port_builder);
        };
        let mut port = port_builder.open().unwrap_or_else(|e| {
            // check error type not found and display short error message
            if e.kind() == serial_port::ErrorKind::Io(io::ErrorKind::NotFound) {
                eprintln!("Serial port {} not found.", opt.port.as_str());
                // output full error message in debug mode
                if opt.debug {
                    eprintln!("Debug Mode: Serial Port {} {:?}", opt.port.as_str(), e);
                };
                std::process::exit(1); // exit with error
            } else {
                // any over error display full error message
                eprintln!("Serial Port {} {:?}", opt.port.as_str(), e);
                std::process::exit(1); // exit with error
            }
        });

        write_port(&mut port);

        read_port(port);

        // exit with no error
        std::process::exit(0);
    }
}

fn write_port(port: &mut Box<dyn SerialPort>) {
    let output = "This is a test. This is only a test.".as_bytes();
    let bytes_sent = port.write(output).unwrap_or_else(|e| {
        std::process::exit(1);
    });
    print!("bytes sent {} \n", bytes_sent.to_string());
}

fn read_port(mut port: Box<dyn SerialPort>) {
    let mut serial_buf: Vec<u8> = vec![0; 32];
    let _bytes_read = port
        .read(serial_buf.as_mut_slice())
        .expect("Error reading from the serial port !");
    println!(
        "Read from serial port \n{:?}\n",
        serial_buf.to_ascii_lowercase()
    );
}

fn com_list_info() {
    match available_ports() {
        Ok(ports) => {
            match ports.len() {
                0 => println!("No ports found."),
                1 => println!("Found 1 port:"),
                n => println!("Found {} ports:", n),
            };
            for p in ports {
                println!("\n  {}", p.port_name);
                match p.port_type {
                    SerialPortType::UsbPort(info) => {
                        println!("      Type:  USB");
                        println!("      VID:   {:04x}", info.vid);
                        println!("      PID:   {:04x}", info.pid);
                        println!(
                            "      Serial Number:   {}",
                            info.serial_number.as_ref().map_or("", String::as_str)
                        );
                        println!(
                            "      Manufacturer:    {}",
                            info.manufacturer.as_ref().map_or("", String::as_str)
                        );
                        println!(
                            "      Manufacturer database:    {}",
                            info.manufacturer_database
                                .as_ref()
                                .map_or("", String::as_str)
                        );
                        println!(
                            "      Product:         {}",
                            info.product.as_ref().map_or("", String::as_str)
                        );
                        println!(
                            "      Product database:         {}",
                            info.product_database.as_ref().map_or("", String::as_str)
                        );
                    }
                    SerialPortType::BluetoothPort => {
                        println!("    Type: Bluetooth");
                    }
                    SerialPortType::PciPort => {
                        println!("    Type: PCI");
                    }
                    SerialPortType::Unknown => {
                        println!("    Type: Unknown");
                    }
                }
            }
        }
        Err(e) => {
            eprintln!("{:?}", e);
            eprintln!("Error listing serial ports");
        }
    }
}
/*


*/
//fn com_write(port:&SerialPort>){
//    let output = "This is a test. This is only a test.".as_bytes();
//    port.write(output).expect("Write failed!");
//}

//fn com_read(port:&SerialPortType){
//    let mut serial_buf: Vec<u8> = vec![0; 32];
//port.read(serial_buf.as_mut_slice()).expect("Found no data!");
//
//}
/*
fn com_native(){
    let port = serialport::new("/dev/ttyUSB0", 115_200)
    .open_native().expect("Failed to open port");

}
*/
