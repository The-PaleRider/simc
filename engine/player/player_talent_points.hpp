// ==========================================================================
// Dedmonwakeen's Raid DPS/TPS Simulator.
// Send questions to natehieter@gmail.com
// ==========================================================================

#pragma once

#include "config.hpp"
#include "util/generic.hpp"
#include "util/span.hpp"
#include "sc_enums.hpp"
#include <array>
#include <vector>
#include <functional>
#include <string>

struct spell_data_t;

// Talent Translation =======================================================

constexpr int MAX_TALENT_ROWS = 7;
constexpr int MAX_TALENT_COLS = 3;
constexpr int MAX_TALENT_SLOTS = MAX_TALENT_ROWS * MAX_TALENT_COLS;

struct player_talent_points_t
{
public:
  using validity_fn_t = std::function<bool(const spell_data_t*)>;

  player_talent_points_t() { clear(); }

  int choice( int row ) const
  {
    row_check( row );
    return _choices[ row ];
  }

  util::span<const int> choices() const;

  void clear( int row )
  {
    row_check( row );
    _choices[ row ] = -1;
  }

  bool has_row_col( int row, int col ) const
  { return choice( row ) == col; }

  void select_row_col( int row, int col )
  {
    row_col_check( row, col );
    _choices[ row ] = col;
  }

  void clear();
  std::string to_string() const;

  bool validate( const spell_data_t* spell, int row, int col ) const;

  void register_validity_fn( const validity_fn_t& fn )
  { _validity_fns.push_back( fn ); }

private:
  std::array<int, MAX_TALENT_ROWS> _choices;
  std::vector<validity_fn_t> _validity_fns;

  static void row_check( int row )
  { assert( row >= 0 && row < MAX_TALENT_ROWS ); ( void )row; }

  static void column_check( int col )
  { assert( col >= 0 && col < MAX_TALENT_COLS ); ( void )col; }

  static void row_col_check( int row, int col )
  { row_check( row ); column_check( col ); }

};
