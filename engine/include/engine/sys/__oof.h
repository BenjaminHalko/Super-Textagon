// https://github.com/s9w/oof

#pragma once

#include <functional>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace oof
{
   // Feel free to bit_cast, reinterpret_cast or memcpy your 3-byte color type into this.
   struct color {
      uint8_t red{}, green{}, blue{};
      constexpr color() = default;

      template<std::integral component_type>
      constexpr color(component_type r, component_type g, component_type b)
         : red{ static_cast<uint8_t>(r) }
         , green{ static_cast<uint8_t>(g) }
         , blue{ static_cast<uint8_t>(b) }
      {}

      template<std::integral component_type>
      constexpr color(component_type component)
         : color(component, component, component)
      {}

      friend constexpr auto operator==(const color&, const color&) -> bool = default;
   };
   

   // Necessary forward declarations
   struct fg_rgb_color_sequence; struct fg_index_color_sequence;
   struct bg_rgb_color_sequence; struct bg_index_color_sequence;
   struct set_index_color_sequence;
   struct bold_sequence; struct cursor_visibility_sequence; struct underline_sequence;
   struct position_sequence; struct hposition_sequence; struct vposition_sequence;
   struct move_left_sequence; struct move_right_sequence; struct move_up_sequence; struct move_down_sequence;
   struct char_sequence; struct wchar_sequence;
   struct reset_sequence; struct clear_screen_sequence;

   // Sets the foreground RGB color
   [[nodiscard]] auto fg_color(const color& col) -> fg_rgb_color_sequence;

   // Sets the foreground indexed color. Index must be in [1, 255]. You can define colors with set_index_color().
   [[nodiscard]] auto fg_color(int index) -> fg_index_color_sequence;

   // Sets the background RGB color
   [[nodiscard]] auto bg_color(const color& col) -> bg_rgb_color_sequence;

   // Sets the background indexed color. Index must be in [1, 255]. You can define colors with set_index_color().
   [[nodiscard]] auto bg_color(int index) -> bg_index_color_sequence;

   // Sets the indexed color. Index must be in [1, 255].
   [[nodiscard]] auto set_index_color(int index, const color& col) -> set_index_color_sequence;

   // Sets the underline state of the console
   [[nodiscard]] auto underline(bool new_value = true) -> underline_sequence;

   // Sets the bold state of the console. Warning: Bold is not supported by all console, see readme
   [[nodiscard]] auto bold(bool new_value = true) -> bold_sequence;

   // Sets cursor visibility state. Recommended to turn off before doing real-time displays
   [[nodiscard]] auto cursor_visibility(bool new_value) -> cursor_visibility_sequence;

   // Resets foreground- and background color, underline and bold state
   [[nodiscard]] auto reset_formatting() -> reset_sequence;

   // Clears the screen
   [[nodiscard]] auto clear_screen() -> clear_screen_sequence;

   // Sets the cursor position. Zero-based
   [[nodiscard]] auto position(int line, int column) -> position_sequence;
   [[nodiscard]] auto vposition(int line) -> vposition_sequence;
   [[nodiscard]] auto hposition(int column) -> hposition_sequence;

   // Moves the cursor a certain amount
   [[nodiscard]] auto move_left(int amount) -> move_left_sequence;
   [[nodiscard]] auto move_right(int amount) -> move_right_sequence;
   [[nodiscard]] auto move_up(int amount) -> move_up_sequence;
   [[nodiscard]] auto move_down(int amount) -> move_down_sequence;


   using error_callback_type = void(*)(const std::string& msg);
   inline error_callback_type error_callback = nullptr;

   template<typename T, typename ... types>
   constexpr bool is_any_of = (std::same_as<T, types> || ...);
   template<typename T>
   concept std_string_type = is_any_of<T, std::string, std::wstring>;

   template<typename T, typename variant_type>
   struct is_alternative : std::false_type {};
   template<typename T, typename ... variant_alternatives>
   struct is_alternative<T, std::variant<variant_alternatives...>>
      : std::disjunction<std::is_same<T, variant_alternatives>...> {};
   template<typename T, typename variant_type>
   constexpr bool is_alternative_v = is_alternative<T, variant_type>::value;

   using sequence_variant_type = std::variant<
      fg_rgb_color_sequence, fg_index_color_sequence, bg_index_color_sequence, bg_rgb_color_sequence, set_index_color_sequence,
      position_sequence, hposition_sequence, vposition_sequence,
      underline_sequence, bold_sequence, char_sequence, wchar_sequence, reset_sequence, clear_screen_sequence, cursor_visibility_sequence,
      move_left_sequence, move_right_sequence, move_up_sequence, move_down_sequence
   >;

   template<typename T>
   concept sequence_c = is_alternative_v<T, sequence_variant_type>;

   
   // Writes a single sequence type into a string
   template<oof::std_string_type string_type, oof::sequence_c sequence_type>
   auto write_sequence_into_string(string_type& target, const sequence_type& sequence) -> void;

   // Returns a sing from a sequence type
   template<oof::std_string_type string_type, oof::sequence_c sequence_type>
   [[nodiscard]] auto get_string_from_sequence(const sequence_type& sequence) -> string_type;

   // Returns a string from a vector of sequence types
   template<oof::std_string_type string_type>
   [[nodiscard]] auto get_string_from_sequences(const std::vector<sequence_variant_type>& sequences) -> string_type;

   // Returns the exact size a string from this vector of sequence types
   [[nodiscard]] auto get_string_reserve_size(const std::vector<sequence_variant_type>& sequences) -> size_t;
   

   struct cell_format {
      bool m_underline = false;
      bool m_bold = false;
      color m_fg_color{255, 255, 255};
      color m_bg_color{0, 0, 0};
      friend constexpr auto operator==(const cell_format&, const cell_format&) -> bool = default;
   };


   template<oof::std_string_type string_type>
   struct cell {
      using char_type = typename string_type::value_type;

      char_type m_letter{};
      cell_format m_format{};
      friend constexpr auto operator==(const cell&, const cell&) -> bool = default;
   };


   template<oof::std_string_type string_type>
   struct screen{
      using char_type = typename string_type::value_type;

      explicit screen(int width, int height, int start_column, int start_line, const cell<string_type>& background);

      // This constructor taking a fill_char implies black background, white foreground color
      explicit screen(int width, int height, int start_column, int start_line, char_type fill_char);

      // This constructor taking a fill_char implies black background, white foreground color and top left start
      explicit screen(int width, int height, char_type fill_char);

      [[nodiscard]] auto get_width() const -> int;
      [[nodiscard]] auto get_height() const -> int;
      
      [[nodiscard]] auto get_cell (int column, int line) -> cell<string_type>&;
      [[nodiscard]] auto is_inside(int column, int line) const -> bool;
      [[nodiscard]] auto get_string(                   ) const -> string_type;
                    auto get_string(string_type& buffer) const -> void;

      // This writes a text into the screen cells
      auto write_into(const string_type& text, int column, int line, const cell_format& formatting) -> void;

      // Override all cells with the background state
      auto clear() -> void;

      [[nodiscard]] auto begin() const { return std::begin(m_cells); }
      [[nodiscard]] auto begin()       { return std::begin(m_cells); }
      [[nodiscard]] auto end()   const { return std::end(m_cells); }
      [[nodiscard]] auto end()         { return std::end(m_cells); }

   private:
      auto update_sequence_buffer() const -> void;

      int m_width = 0;
      int m_height = 0;
      int m_origin_line = 0;
      int m_origin_column = 0;
      cell<string_type> m_background;
      std::vector<cell<string_type>> m_cells;
      mutable std::vector<cell<string_type>> m_old_cells;
      mutable std::vector<sequence_variant_type> m_sequence_buffer;
   };
   

   struct pixel_screen {
      std::vector<color> m_pixels;

      explicit pixel_screen(int width, int halfline_height, int start_column, int start_halfline, const color& fill_color);

      // This will init with black fill color
      explicit pixel_screen(int width, int halfline_height, int start_column, int start_halfline);

      // This will init with black fill color and starting at the top left
      explicit pixel_screen(int width, int halfline_height);

      [[nodiscard]] auto begin() const { return std::begin(m_pixels); }
      [[nodiscard]] auto begin()       { return std::begin(m_pixels); }
      [[nodiscard]] auto end()   const { return std::end(m_pixels); }
      [[nodiscard]] auto end()         { return std::end(m_pixels); }
      
      [[nodiscard]] auto get_string(                    ) const -> std::wstring;
                    auto get_string(std::wstring& buffer) const -> void;
      [[nodiscard]] auto get_width() const -> int;
      [[nodiscard]] auto get_halfline_height() const -> int;

      // If you want to override something in the screen
      [[nodiscard]] auto get_screen_ref() -> screen<std::wstring>&;

      // Override all pixels with the fill color
                    auto clear() -> void;
      
      [[nodiscard]] auto get_color(int column, int halfline) const -> const color&;
      [[nodiscard]] auto get_color(int column, int halfline)       -> color&;
      [[nodiscard]] auto is_in    (int column, int halfline) const -> bool;

   private:
      [[nodiscard]] auto get_line_height() const -> int;
      auto compute_result() const -> void;

      color m_fill_color{};
      int m_halfline_height = 0; // This refers to "pixel" height. Height in lines will be half that.
      int m_origin_column = 0;
      int m_origin_halfline = 0;
      mutable screen<std::wstring> m_screen;
   };



   // Deduction guide
   template<typename char_type>
   screen(int, int, int, int, char_type fill_char) -> screen<std::basic_string<char_type>>;
   template<typename char_type>
   screen(int, int, char_type fill_char) -> screen<std::basic_string<char_type>>;

   template<typename stream_type, oof::sequence_c sequence_type>
   auto operator<<(stream_type& os, const sequence_type& sequence) -> stream_type&;

   namespace detail
   {

      // CRTP to extend the numerous sequence types with convenience member functions without using runtime
      // polymorphism or repeating the code
      template<typename T>
      struct extender {
         operator std::string() const;
         operator std::wstring() const;
         [[nodiscard]] auto operator+(const std::string&  other) const -> std::string;
         [[nodiscard]] auto operator+(const std::wstring& other) const -> std::wstring;
      };

      auto error(const std::string& msg) -> void;

      [[nodiscard]] auto get_pixel_background(const color& fill_color) -> cell<std::wstring>;

      template<oof::std_string_type string_type>
      auto write_sequence_string_no_reserve(const std::vector<sequence_variant_type>& sequences, string_type& target) -> void;

      template<oof::sequence_c sequence_type>
      [[nodiscard]] constexpr auto get_sequence_string_size(const sequence_type& sequence) -> size_t;

      template<oof::std_string_type string_type, std::integral int_type>
      auto write_int_to_string(string_type& target, const int_type value, const bool with_leading_semicolon) -> void;

      struct cell_pos {
         int m_index = 0;
         int m_width = 0;
         int m_height = 0;

         explicit constexpr cell_pos(const int width, const int height)
            : m_width(width)
            , m_height(height)
         {}
         [[nodiscard]] constexpr auto get_column() const -> int {
            return m_index % m_width;
         }
         [[nodiscard]] constexpr auto get_line() const -> int {
            return m_index / m_width;
         }
         [[nodiscard]] constexpr auto is_end() const -> bool {
            return m_index >= (m_width * m_height);
         }
         [[nodiscard]] constexpr auto operator+(const int jump_amount) const -> cell_pos {
            cell_pos jumped_pos(m_width, m_height);
            jumped_pos.m_index = m_index + jump_amount;
            return jumped_pos;
         }
         constexpr auto operator++() -> cell_pos& {
            ++m_index;
            return *this;
         }
         friend constexpr auto operator==(const cell_pos&, const cell_pos&) -> bool = default;
      };


      template<oof::std_string_type string_type>
      struct draw_state{
         using cell_type = cell<string_type>;
         std::optional<cell_pos> m_last_written_pos;
         std::optional<cell_format> m_format;
         
         explicit draw_state() = default;

         auto write_sequence(
            std::vector<sequence_variant_type>& sequence_buffer,
            const cell_type& target_cell_state,
            const std::optional<std::reference_wrapper<const cell_type>>& old_cell_state,
            const cell_pos& target_pos,
            const int origin_line,
            const int origin_column
         ) -> void;

      private:
         [[nodiscard]] auto is_position_sequence_necessary(const cell_pos& target_pos) const -> bool;
      };

      template<oof::std_string_type string_type, typename T, typename ... Ts>
      auto write_ints_into_string(string_type& target, const T& first, const Ts&... rest) -> void;

      template<oof::std_string_type string_type>
      [[nodiscard]] auto get_index_color_seq_str(const set_index_color_sequence& sequence) -> string_type;

      template<std_string_type string_type>
      using fitting_char_sequence_t = std::conditional_t<std::is_same_v<string_type, std::string>, char_sequence, wchar_sequence>;

   } // namespace detail


   struct fg_rgb_color_sequence : detail::extender<fg_rgb_color_sequence> {
      color m_color;
   };
   struct fg_index_color_sequence : detail::extender<fg_index_color_sequence> {
      int m_index;
   };
   struct set_index_color_sequence : detail::extender<set_index_color_sequence> {
      int m_index{};
      color m_color;
   };
   struct bg_rgb_color_sequence : detail::extender<bg_rgb_color_sequence> {
      color m_color;
   };
   struct bg_index_color_sequence : detail::extender<bg_index_color_sequence> {
      int m_index;
   };
   struct underline_sequence : detail::extender<underline_sequence> {
      bool m_underline;
   };
   struct bold_sequence : detail::extender<bold_sequence> {
      bool m_bold;
   };
   struct cursor_visibility_sequence : detail::extender<cursor_visibility_sequence> {
      bool m_visibility;
   };
   struct position_sequence : detail::extender<position_sequence> {
      uint8_t m_line;
      uint8_t m_column;
   };
   struct hposition_sequence : detail::extender<hposition_sequence> {
      uint8_t m_column;
   };
   struct vposition_sequence : detail::extender<vposition_sequence> {
      uint8_t m_line;
   };
   struct move_left_sequence : detail::extender<move_left_sequence> {
      uint8_t m_amount;
   };
   struct move_right_sequence : detail::extender<move_right_sequence> {
      uint8_t m_amount;
   };
   struct move_up_sequence : detail::extender<move_up_sequence> {
      uint8_t m_amount;
   };
   struct move_down_sequence : detail::extender<move_down_sequence> {
      uint8_t m_amount;
   };
   struct char_sequence : detail::extender<char_sequence> {
      char m_letter;
   };
   struct wchar_sequence : detail::extender<wchar_sequence> {
      wchar_t m_letter;
   };
   struct reset_sequence : detail::extender<reset_sequence> {};
   struct clear_screen_sequence : detail::extender<clear_screen_sequence> {};

} // namespace oof


// Constexpr, therefore defined here
template<oof::sequence_c sequence_type>
constexpr auto oof::detail::get_sequence_string_size(const sequence_type& sequence) -> size_t
{
   constexpr auto get_int_param_str_length = [](const int param) -> int {
      if (param < 10)  return 1;
      if (param < 100) return 2;
                       return 3;
   };

   if constexpr (is_any_of<sequence_type, char_sequence, wchar_sequence>) {
      return 1;
   }
   else if constexpr (std::is_same_v<sequence_type, set_index_color_sequence>) {
      size_t reserve_size = 0;
      reserve_size += 4; // \x1b]4;
      reserve_size += get_int_param_str_length(sequence.m_index); // <i>;
      reserve_size += 4; // ;rgb:

      constexpr auto get_component_str_size = [](const uint8_t component) {
         return component < 15 ? 2 : 1;
      };
      reserve_size += get_component_str_size(sequence.m_color.red);
      reserve_size += 1; // /
      reserve_size += get_component_str_size(sequence.m_color.green);
      reserve_size += 1; // /
      reserve_size += get_component_str_size(sequence.m_color.blue);
      reserve_size += 2; // <ST>

      return reserve_size;
   }
   else {
      size_t reserve_size = 0;
      constexpr int semicolon_size = 1;
      if constexpr (is_any_of<sequence_type, fg_rgb_color_sequence, bg_rgb_color_sequence>) {
         reserve_size += 2 + semicolon_size + 1 +
            semicolon_size + get_int_param_str_length(sequence.m_color.red) +
            semicolon_size + get_int_param_str_length(sequence.m_color.green) +
            semicolon_size + get_int_param_str_length(sequence.m_color.blue);
      }
      else if constexpr (std::is_same_v<sequence_type, underline_sequence>)
      {
         reserve_size += sequence.m_underline ? 1 : 2;
      }
      else if constexpr (std::is_same_v<sequence_type, bold_sequence>)
      {
         reserve_size += sequence.m_bold ? 1 : 2;
      }
      else if constexpr (std::is_same_v<sequence_type, position_sequence>)
      {
         reserve_size += get_int_param_str_length(sequence.m_line);
         reserve_size += semicolon_size;
         reserve_size += get_int_param_str_length(sequence.m_column);
      }
      else if constexpr (std::is_same_v<sequence_type, hposition_sequence>) {
         reserve_size += get_int_param_str_length(sequence.m_column);
      }
      else if constexpr (std::is_same_v<sequence_type, vposition_sequence>) {
         reserve_size += get_int_param_str_length(sequence.m_line);
      }
      else if constexpr (is_any_of<sequence_type, reset_sequence, clear_screen_sequence>)
      {
         reserve_size += 1;
      }
      else if constexpr (is_any_of<sequence_type, cursor_visibility_sequence>)
      {
         reserve_size += 3;
      }
      else if constexpr (is_any_of<sequence_type, move_left_sequence, move_right_sequence, move_up_sequence, move_down_sequence>)
      {
         reserve_size += get_int_param_str_length(sequence.m_amount);
      }
      else if constexpr (std::is_same_v<sequence_type, fg_index_color_sequence>)
      {
         reserve_size += 5; // "38;5;"
         reserve_size += get_int_param_str_length(sequence.m_index);
      }

      reserve_size += 3; // 2 intro, 1 outro
      return reserve_size;
   }
}


// This will deliberately be instantiated at compiletime
template<typename stream_type, oof::sequence_c sequence_type>
auto oof::operator<<(stream_type& os, const sequence_type& sequence) -> stream_type&
{
   using char_type = typename stream_type::char_type;
   using string_type = std::basic_string<char_type>;
   string_type temp_string{};
   temp_string.reserve(detail::get_sequence_string_size(sequence));
   write_sequence_into_string(temp_string, sequence);
   os << temp_string;
   return os;
}
