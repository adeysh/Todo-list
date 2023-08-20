# Todo-List Maker (Updated by VladRumsh)

The Todo-List Maker is a robust command-line application that builds upon the foundation of the original "Todo-list". This refined version incorporates various optimizations and features, ensuring a streamlined and user-friendly experience.

## Features
- **Add new Todos.**
- **Mark Todos as completed.**
- **Remove Todos.**
- **Clear and user-friendly interface.**

## Key Updates & Rationale

### ID Optimization
- Transitioned the data type of `id` from `int` to `unsigned char`.
    - Benefit: While the original code supported up to 100 IDs, the `unsigned char` expands this range to 256 but with significantly reduced memory consumption.

### Unique ID Management
- Integrated a `std::set` to monitor and manage used IDs.
    - Benefit: This system ensures IDs remain unique, effectively eliminating potential overlaps and conflicts.

### Debugging and Testing
- Implemented the `numberOfIds` constant for controlled testing and debugging purposes.
    - Benefit: Provides an avenue for controlled tests, particularly when evaluating behaviors near the ID threshold.

### MBCS Support
- Transitioned from `string` to `wstring` to cater to a wider range of character sets.
    - Benefit: This change bolsters the application's versatility, enabling support for multi-byte character sets (MBCS).

### Enhanced Input Handling
- Implemented mechanisms to clear the input buffer post input reception.
    - Benefit: This minimizes potential errors stemming from unwanted or residual input data.

### Enhanced Usability
- Enhanced the interface to notify users upon reaching the maximum Todo capacity.
    - Benefit: Direct feedback enhances the user experience by providing actionable insights.

### Namespace Handling
- Removed the `using namespace std` directive.
    - Benefit: Reduces namespace pollution and naming conflicts.

### Error Handling
- **Invalid ID Entry**: The system handles non-existent IDs gracefully.
- **Max Todos Capacity**: Clear feedback is provided upon reaching the Todos limit.
- **Input Buffer Handling**: Resilience to unintended or residual inputs, ensuring consistent outcomes.

## Future Improvements and Suggestions
- **Code Modularization**: Promote readability and maintenance.
- **Persistent Storage**: Enable list maintenance across sessions.
- **Sorting and Searching**: Manage large lists with ease.
