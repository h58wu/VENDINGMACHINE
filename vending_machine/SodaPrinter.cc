#include <uC++.h>
#include "SodaNameServer.h"
#include "MPRNG.h"
#include "SodaBank.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;                    // direct access to std
#include <cstdlib>
#include "SodaPrinter.h"
#include "SodaVendingMachine.h"
#include "SodaBottlingPlant.h"
#include "SodaParent.h"
#include "SodaStudent.h"
#include "SodaTruck.h"
#include "SodaWatCard.h"


Printer::Printer (unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ){
  cout << "Parent\tWATOff\tNames\tTruck\tPlant\t";
  this->numStudents = numStudents;
  this->numCouriers = numCouriers;
  this->numVendingMachines = numVendingMachines;
  for (int i = 0; i < numStudents; i++){
    cout << "Stud" << i << "\t";
  }// end for
  for (int i = 0; i < numVendingMachines; i++){
    cout << "Mach" << i << "\t";
  }// end for
  for (int i = 0; i < numCouriers; i++){
    cout << "Cour" << i << "\t";
  }// end for
  cout << endl;
  total = numStudents + numVendingMachines + numCouriers + 5;
  for (int i = 0; i < total; i++){
    cout <<"*******\t";
    info temp;
    temp.id = -1;
    v.push_back(temp);   
  } // end for
  cout << endl;
}

Printer::~Printer(){
  cout << "******************" << endl;
}

bool Printer::checkKind(Kind kind) { // checks if there is an update to the buffer
  if (kind == Parent){
    if (v[0].id == -1) {
      return false;
    }
  }
  else if (kind == WATCardOffice){
    if (v[1].id == -1) {
      return false;
    }
  }
  else if (kind == NameServer){
    if (v[2].id == -1) {
      return false;
    }
  }
  else if (kind == Truck){
    if (v[3].id == -1) {
      return false;
    }
  }
  else if (kind == BottlingPlant){
    if (v[4].id == -1) {
      return false;
    }
  }
  return true;
}

bool Printer::checkKind(Kind kind, int id ) { // checks if there is an update to the buffer
  if (kind == Student){
    if (v[id].id == -1) {
      return false;
    }
  }
  else if (kind == Vending){
    if (v[id].id == -1) {
      return false;
    }
  }
  else if (kind == Courier){
    if (v[id].id == -1) {
      return false;
    }
  }
  return true;
}

void Printer::printHelper(info i) { // given a struck info it will print out the corresponding information given
  if(i.kind == Parent) {
    if(i.state == 'D'){
      cout << "D" << i.value1 << "," << i.value2 << "\t";
      return;
    }
    else if (i.state == 'S') {
      cout << "S\t";
      return;
    }
  }
  else if(i.kind == WATCardOffice) {
    if (i.state == 'W') {
      cout << "W\t";
      return;
    }
    else if(i.state == 'C') {
      cout << "C" << i.value1 << "," << i.value2 << "\t";
      return;
    }
    else if(i.state == 'T') {
      cout << "T" << i.value1 << "," << i.value2 << "\t";
      return;
    }
    else if (i.state == 'S') {
      cout << "S\t";
      return;
    }
  }
  else if(i.kind == NameServer) {
    if (i.state == 'R') {
      cout << "R" << i.value1 << "\t";
      return;
    }
    else if(i.state == 'N') {
      cout << "N" << i.value1 << "," << i.value2 << "\t";
      return;
    }
    else if (i.state == 'S') {
      cout << "S\t";
      return;
    }
  }
  else if(i.kind == Truck) {
    if (i.state == 'P') {
      cout << "P" << i.value1 << "\t";
      return;
    }
    else if(i.state == 'd') {
      cout << "d" << i.value1 << "," << i.value2 << "\t";
      return;
    }
    else if(i.state == 'U') {
      cout << "U" << i.value1 << "," << i.value2 << "\t";
      return;
    }
    else if(i.state == 'D') {
      cout << "D" << i.value1 << "," << i.value2 << "\t";
      return;
    }
    else if (i.state == 'S') {
      cout << "S\t";
      return;
    }
  }
  else if(i.kind == BottlingPlant) {
    if (i.state == 'G') {
      cout << "G" << i.value1 << "\t";
      return;
    }
    else if(i.state == 'P') {
      cout << "P\t";
      return;
    }
    else if (i.state == 'S') {
      cout << "S\t";
      return;
    }
  }
  else if(i.kind == Student) {
    if (i.state == 'V') {
      cout << "V" << i.value1 << "\t";
      return;
    }
    else if (i.state == 'B') {
      cout << "B" << i.value1 << "\t";
      return;
    }
    else if(i.state == 'L') {
      cout << "L\t";
      return;
    }
    else if (i.state == 'S') {
      cout << "S"<< i.value1 << "," << i.value2 << "\t";
      return;
    }
  }
  else if(i.kind == Vending) {
    if (i.state == 'r') {
      cout << "r\t";
      return;
    }
    else if (i.state == 'R') {
      cout << "R\t";
      return;
    }
    else if (i.state == 'B') {
      cout << "B"<< i.value1 << "," << i.value2 << "\t";
      return;
    }
    else if (i.state == 'S') {
      cout << "S"<< i.value1  << "\t";
      return;
    }
  }
  else if(i.kind == Courier) {
    if (i.state == 'S') {
      cout << "S\t";
      return;
    }
    else if(i.state == 't') {
      cout << "t" << i.value1 << "," << i.value2 << "\t";
      return;
    }
    else if(i.state == 'T') {
      cout << "T" << i.value1 << "," << i.value2 << "\t";
      return;
    }
  }
}

void Printer::print( Kind kind, char state ){
  if (checkKind(kind)) {
    for (int i = 0; i < v.size(); i++) {
      if (v[i].id == -1) {
        cout << "\t";
      }
      else {
        printHelper(v[i]);
      }
      v[i].id = -1;
    }
    cout << endl;
  }

  int id = 0;
  if (kind == Parent){
    id = 0;
  }
  else if (kind == WATCardOffice){
    id = 1;
  }
  else if (kind == NameServer){
    id = 2;
  }
  else if (kind == Truck){
    id = 3;
  }
  else if (kind == BottlingPlant){
    id = 4;
  }

  if (state == 'F') {
    for (int i = 0; i < total; i++) {
      if (i == id){
        cout << "F\t";
      }
      else {
        cout << "...\t";
      }
    }
    cout << endl;
  }
  else {
    v[id].id = 1;
    v[id].state = state;
    v[id].kind = kind;
  }
}

void Printer::print( Kind kind, char state, int value1 ){
  if (checkKind(kind)) {
    for (int i = 0; i < v.size(); i++) {
      if (v[i].id == -1) {
        cout << "\t";
      }
      else {
        printHelper(v[i]);
      }
      v[i].id = -1;
    }
    cout << endl;
  }

  int id = 0;
  if (kind == Parent){
    id = 0;
  }
  else if (kind == WATCardOffice){
    id = 1;
  }
  else if (kind == NameServer){
    id = 2;
  }
  else if (kind == Truck){
    id = 3;
  }
  else if (kind == BottlingPlant){
    id = 4;
  }

  if (state == 'F') {
    for (int i = 0; i < total; i++) {
      if (i == id){
        cout << "F\t";
      }
      else {
        cout << "...\t";
      }
    }
    cout << endl;
  }
  else {
    v[id].id = 1;
    v[id].state = state;
    v[id].value1 = value1;
    v[id].kind = kind;
  }
}

void Printer::print( Kind kind, char state, int value1, int value2 ){
  if (checkKind(kind)) {
    for (int i = 0; i < v.size(); i++) {
      if (v[i].id == -1) {
        cout << "\t";
      }
      else {
        printHelper(v[i]);
      }
      v[i].id = -1;
    }
    cout << endl;
  }

  int id = 0;
  if (kind == Parent){
    id = 0;
  }
  else if (kind == WATCardOffice){
    id = 1;
  }
  else if (kind == NameServer){
    id = 2;
  }
  else if (kind == Truck){
    id = 3;
  }
  else if (kind == BottlingPlant){
    id = 4;
  }

  if (state == 'F') {
    for (int i = 0; i < total; i++) {
      if (i == id){
        cout << "F\t";
      }
      else {
        cout << "...\t";
      }
    }
    cout << endl;
  }
  else {
    v[id].id = 1;
    v[id].state = state;
    v[id].value1 = value1;
    v[id].value2 = value2;
    v[id].kind = kind;
  }
}

void Printer::print( Kind kind, unsigned int lid, char state ){
  if (kind == Student) {
    lid += 5;
  }
  else if (kind == Vending) {
    lid += 5 + numStudents;
  }
  else if (kind == Courier) {
    lid += 5 + numStudents + numVendingMachines;
  }

  if (checkKind(kind, lid)) {
    for (int i = 0; i < v.size(); i++) {
      if (v[i].id == -1) {
        cout << "\t";
      }
      else {
        printHelper(v[i]);
      }
      v[i].id = -1;
    }
    cout << endl;
  }

  if (state == 'F') {
    for (int i = 0; i < total; i++) {
      if (i == lid){
        cout << "F\t";
      }
      else {
        cout << "...\t";
      }
    }
    cout << endl;
  }
  else {
    v[lid].id = 1;
    v[lid].state = state;
    v[lid].kind = kind;
  }
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ){
  if (kind == Student) {
    lid += 5;
  }
  else if (kind == Vending) {
    lid += 5 + numStudents;
  }
  else if (kind == Courier) {
    lid += 5 + numStudents + numVendingMachines;
  }

  if (checkKind(kind, lid)) {
    for (int i = 0; i < v.size(); i++) {
      if (v[i].id == -1) {
        cout << "\t";
      }
      else {
        printHelper(v[i]);
      }
      v[i].id = -1;
    }
    cout << endl;
  }

  if (state == 'F') {
    for (int i = 0; i < total; i++) {
      if (i == lid){
        cout << "F\t";
      }
      else {
        cout << "...\t";
      }
    }
    cout << endl;
  }
  else {
    v[lid].id = 1;
    v[lid].state = state;
    v[lid].value1 = value1;
    v[lid].kind = kind;
    //cout <<"lid: "<< lid<< " state: " << state << " value1: "<< value1 << " kind: " << kind;
  }
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ){
  //cout <<"****lid: "<< lid<< " state: " << state << " value1: "<< value1 << " value2: "<< value2<< " kind: " << kind << endl;
  if (kind == Student) {
    lid += 5;
  }
  else if (kind == Vending) {
    lid += 5 + numStudents;
  }
  else if (kind == Courier) {
    lid += 5 + numStudents + numVendingMachines;
  }

  if (checkKind(kind, lid)) {
    for (int i = 0; i < v.size(); i++) {
      if (v[i].id == -1) {
        cout << "\t";
      }
      else {
        printHelper(v[i]);
      }
      v[i].id = -1;
    }
    cout << endl;
  }

  if (state == 'F') {
    for (int i = 0; i < total; i++) {
      if (i == lid){
        cout << "F\t";
      }
      else {
        cout << "...\t";
      }
    }
    cout << endl;
  }
  else {
    v[lid].id = 1;
    v[lid].state = state;
    v[lid].value1 = value1;
    v[lid].value2 = value2;
    v[lid].kind = kind;
    //cout <<"lid: "<< lid<< " state: " << state << " value1: "<< value1 << " value2: "<< value2<< " kind: " << kind << endl;
  }
}
