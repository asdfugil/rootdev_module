# rootdev_module

PongoOS module that patches /chosen/root-matching in the DeviceTree.

## Building

To build, set the `PONGO_SRC` environmental variable to the path to the 
PongoOS source tree, then just `make all`.

## Usage

`set_rootdev <new disk>`

Example: `set_rootdev disk0s1s8`
